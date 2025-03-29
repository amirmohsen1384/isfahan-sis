#include "include/models/enrolledmodel.h"

EnrolledModel::EnrolledModel(const Teacher &teacher, QObject *parent) : EnrolledModel(parent)
{
    setTeacher(teacher);
}

EnrolledModel::EnrolledModel(QObject *parent) : QAbstractItemModel(parent)
{
    connect(this, &EnrolledModel::teacherChanged, this, &EnrolledModel::populateModel);
}

EnrolledModel::~EnrolledModel()
{
    resetModel();
}

QModelIndex EnrolledModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent)) {
        return {};
    }

    EntityItem *parentItem = (parent.isValid() ? static_cast<EntityItem*>(parent.internalPointer()) : root);
    EntityItem *item = parentItem->child(row);

    return (item != nullptr ? createIndex(row, column, item) : QModelIndex());
}

QModelIndex EnrolledModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return {};
    }
    EntityItem *item = static_cast<EntityItem*>(index.internalPointer());
    EntityItem *parent = item->parentItem();
    return (parent != nullptr ? createIndex(parent->row(), 0, parent) : QModelIndex{});
}

int EnrolledModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return root->childCount();
    }
    return static_cast<EntityItem*>(parent.internalPointer())->childCount();
}

int EnrolledModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return root->columnCount();
    }
    return static_cast<EntityItem*>(parent.internalPointer())->columnCount();
}

QVariant EnrolledModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return {};
    }
    else if(role == Qt::UserRole) {
        QModelIndex target = this->index(index.row(), 1, index.parent());
        Entity entity(target.data().toLongLong());
        if(index.parent().isValid()) {
            return QVariant::fromValue(Student::loadFromRecord(entity));
        }
        else {
            return QVariant::fromValue(Lesson::loadFromRecord(entity));
        }
    }
    else if(role != Qt::DisplayRole) {
        return {};
    }
    EntityItem *item = static_cast<EntityItem*>(index.internalPointer());
    return item->data(index.column());
}

QVariant EnrolledModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole) {
        switch(orientation) {
        case Qt::Horizontal: {
            return root->data(section);
        }
        case Qt::Vertical: {
            return section + 1;
        }
        }
    }
    return {};
}

Qt::ItemFlags EnrolledModel::flags(const QModelIndex &index) const
{
    return !index.isValid() ? Qt::NoItemFlags : QAbstractItemModel::flags(index);
}

Teacher EnrolledModel::getTeacher() const
{
    return target;
}

void EnrolledModel::setTeacher(const Teacher &teacher)
{
    target = teacher;
    emit teacherChanged(target);
}

void EnrolledModel::resetModel()
{
    if(root != nullptr) {
        delete root;
        root = nullptr;
    }
}

void EnrolledModel::populateModel()
{
    beginResetModel();

    resetModel();
    root = new EntityItem("Name", "ID Number");

    LessonList lessons = target.getLessons();
    for(Lesson lesson : lessons) {
        EntityItem *parent = new EntityItem;

        parent->name = lesson.getName();
        parent->entity = lesson.getIdentifier();

        StudentList container = lesson.getEnrolledStudents();

        for(Student data : container) {
            EntityItem *child = new EntityItem;

            child->parent = parent;
            child->name = data.getFullName();
            child->entity = data.getIdentifier();

            parent->children.append(child);
        }

        root->children.append(parent);
    }

    endResetModel();
}
