#include "include/models/enrolleditem.h"

EnrolledItem::EnrolledItem() {}

EnrolledItem::EnrolledItem(QVariant name, QVariant entity) : EnrolledItem()
{
    this->name = name;
    this->entity = entity;
}

EnrolledItem::~EnrolledItem()
{
    for(EnrolledItem *item : children) {
        delete item;
    }
}

EnrolledItem *EnrolledItem::child(int row)
{
    return children.value(row, nullptr);
}

QVariant EnrolledItem::data(int column) const
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

int EnrolledItem::columnCount() const
{
    return 2;
}

int EnrolledItem::childCount() const
{
    return children.size();
}

EnrolledItem *EnrolledItem::parentItem()
{
    return parent;
}

int EnrolledItem::row() const
{
    if(parent == nullptr) {
        return 0;
    }

    QList<EnrolledItem*> &container = parent->children;
    auto it = std::find_if(container.cbegin(), container.cend(), [this](EnrolledItem *item)
    {
        return item == this;
    });

    if(it != container.cend()) {
        return std::distance(container.cbegin(), it);

    } else {
        return -1;

    }
}
