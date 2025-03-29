#include "include/models/teachingloadmodel.h"
#include "include/data/teacher.h"

TeachingLoadModel::TeachingLoadModel(QObject *parent) : QAbstractItemModel(parent)
{
    populateModel();
}
TeachingLoadModel::~TeachingLoadModel()
{
    delete root;
}

QModelIndex TeachingLoadModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent)) {
        return {};
    }

    EntityItem *parentItem = parent.isValid() ? static_cast<EntityItem*>(parent.internalPointer()) : root;
    EntityItem *item = parentItem->child(row);

    return (item != nullptr ? createIndex(row, column, item) : QModelIndex());
}

QModelIndex TeachingLoadModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return {};
    }
    EntityItem *item = static_cast<EntityItem*>(index.internalPointer());
    EntityItem *parent = item->parentItem();
    return (parent != nullptr ? createIndex(parent->row(), 0, parent) : QModelIndex{});
}

int TeachingLoadModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return root->childCount();
    }
    return static_cast<EntityItem*>(parent.internalPointer())->childCount();
}

int TeachingLoadModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return root->columnCount();
    }
    return static_cast<EntityItem*>(parent.internalPointer())->childCount();
}

QVariant TeachingLoadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }
    else if(role == Qt::UserRole) {
        QModelIndex target = this->index(index.row(), 1, index.parent());
        Entity entity(target.data(Qt::DisplayRole).toLongLong());
        if(!index.parent().isValid()) {
            return QVariant::fromValue(Teacher::loadFromRecord(entity));

        } else {
            return QVariant::fromValue(Lesson::loadFromRecord(entity));

        }
    }
    else if(role != Qt::DisplayRole) {
        return {};
    }
    return static_cast<EntityItem*>(index.internalPointer())->data(index.column());
}

QVariant TeachingLoadModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole) {
        return {};
    } else {
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

void TeachingLoadModel::populateModel()
{
    beginResetModel();

    resetModel();
    root = new EntityItem("Name", "ID Number");

    TeacherList container = Teacher::getEntities();
    for(Teacher one : container) {
        EntityItem *parent = new EntityItem;
        parent->name = one.getFullName();
        parent->entity = one.getIdentifier();

        LessonList lectures = one.getLessons();
        for(Lesson lecture : lectures) {
            EntityItem *item = new EntityItem;

            item->parent = parent;
            item->name = lecture.getName();
            item->entity = lecture.getIdentifier();

            parent->children.append(item);
        }
        root->children.append(parent);
    }

    endResetModel();
}

void TeachingLoadModel::resetModel()
{
    if(root != nullptr) {
        delete root;
        root = nullptr;
    }
}
