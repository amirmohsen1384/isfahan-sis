#include "include/models/core/lecturetreemodel.h"

LectureTreeModel::LectureTreeModel(QObject *parent) : QAbstractItemModel(parent)
{}

LectureTreeModel::~LectureTreeModel()
{
    delete root;
}

QModelIndex LectureTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent)) {
        return {};
    }
    EntityItem *ancestor = (!parent.isValid()) ? root : static_cast<EntityItem*>(parent.internalPointer());
    EntityItem *item = ancestor->child(row);
    return (item != nullptr) ? createIndex(row, column, item) : QModelIndex{};
}

QVariant LectureTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole) {
        return {};
    }
    switch(orientation) {
    case Qt::Horizontal: {
        return root->data(section);
    }
    case Qt::Vertical: {
        return section + 1;
    }
    default: {
        return {};
    }
    }
}

QModelIndex LectureTreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return {};
    } else {
        EntityItem *item = static_cast<EntityItem*>(index.internalPointer());
        return item->parent != nullptr ? createIndex(item->parent->row(), 0, item->parent) : QModelIndex{};
    }
}

void LectureTreeModel::resetModel()
{
    if(root != nullptr) {
        delete root;
        root = nullptr;
    }
}

int LectureTreeModel::rowCount(const QModelIndex &parent) const
{
    EntityItem *item = nullptr;
    if (!parent.isValid()) {
        item = root;
    } else {
        item = static_cast<EntityItem*>(parent.internalPointer());
    }
    return item->childCount();
}

Qt::ItemFlags LectureTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return QAbstractItemModel::flags(index);
}

int LectureTreeModel::columnCount(const QModelIndex &parent) const
{
    EntityItem *item = nullptr;
    if (!parent.isValid()) {
        item = root;
    } else {
        item = static_cast<EntityItem*>(parent.internalPointer());
    }
    return item->columnCount();
}
