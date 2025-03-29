#include "include/models/core/entityitem.h"

EntityItem::EntityItem() {}

EntityItem::EntityItem(QVariant name, QVariant entity) : EntityItem()
{
    this->name = name;
    this->entity = entity;
}

EntityItem::~EntityItem()
{
    for(EntityItem *item : children) {
        delete item;
    }
}

EntityItem *EntityItem::child(int row)
{
    return children.value(row, nullptr);
}

QVariant EntityItem::data(int column) const
{
    switch(column)
    {
    case 0: {
        return name;
    }
    case 1: {
        return entity;
    }
    default: {
        return QVariant();
    }
    }
}

int EntityItem::columnCount() const
{
    return 2;
}

int EntityItem::childCount() const
{
    return children.size();
}

EntityItem *EntityItem::parentItem()
{
    return parent;
}

int EntityItem::row() const
{
    if(parent == nullptr) {
        return 0;
    }

    QList<EntityItem*> &container = parent->children;
    auto it = std::find_if(container.cbegin(), container.cend(), [this](EntityItem *item)
    {
        return item == this;
    });

    if(it != container.cend()) {
        return std::distance(container.cbegin(), it);

    } else {
        return -1;

    }
}

void EntityItem::appendChild(EntityItem *item)
{
    item->parent = this;
    children.append(item);
}
