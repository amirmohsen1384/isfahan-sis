#include "include/models/enrolledmodel.h"

EnrolledModel::EnrolledModel(QObject *parent) : QAbstractItemModel(parent)
{
    connect(this, &EnrolledModel::teacherChanged, this, &EnrolledModel::populateModel);
    populateModel();
}

QModelIndex EnrolledModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent)) {
        return {};
    }

    EnrolledItem *parentItem = (parent.isValid() ? static_cast<EnrolledItem*>(parent.internalPointer()) : root);
    EnrolledItem *item = parentItem->child(row);

    return (item != nullptr ? createIndex(row, column, item) : QModelIndex());
}

QModelIndex EnrolledModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return {};
    }
    EnrolledItem *item = static_cast<EnrolledItem*>(index.internalPointer());
    EnrolledItem *parent = item->parentItem();
    return (parent != nullptr ? createIndex(parent->row(), 0, parent) : QModelIndex{});
}

int EnrolledModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return root->childCount();
    }
    return static_cast<EnrolledItem*>(parent.internalPointer())->childCount();
}

int EnrolledModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return root->columnCount();
    }
    return static_cast<EnrolledItem*>(parent.internalPointer())->columnCount();
}

QVariant EnrolledModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    EnrolledItem *item = static_cast<EnrolledItem*>(index.internalPointer());
    if(index.column() == 1) {
        return qvariant_cast<Entity>(item->data(1)).getIdentifier();

    } else if(index.column() == 0) {
        return item->data(0);
    }
    else {
        return {};
    }
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

void EnrolledModel::updateInspector()
{
    QStringList files = inspector.files();
    if(!files.isEmpty()) {
        inspector.removePaths(files);
    }

    inspector.addPath(Teacher::getFileName(target));

    LessonList lessons = target.getLessons();
    for(Lesson value : lessons) {
        inspector.addPath(Lesson::getFileName(value));
    }
}

void EnrolledModel::populateModel()
{
    beginResetModel();

    resetModel();
    root = new EnrolledItem("Name", "ID Number");

    LessonList lessons = target.getLessons();
    for(Lesson lesson : lessons) {
        EnrolledItem *parent = new EnrolledItem;

        parent->name = lesson.getName();
        parent->entity = QVariant::fromValue(Entity(lesson));

        StudentList container = lesson.getEnrolledStudents();

        for(Student data : container) {
            EnrolledItem *child = new EnrolledItem;

            child->parent = parent;
            child->name = data.getFullName();
            child->entity = QVariant::fromValue(Entity(data));

            parent->children.append(child);
        }

        root->children.append(parent);
    }

    endResetModel();
}
