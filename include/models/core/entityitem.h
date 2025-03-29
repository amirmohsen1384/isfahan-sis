#ifndef ENTITYITEM_H
#define ENTITYITEM_H

#include "include/data/entity.h"
#include <QVariant>

class EntityItem
{
public:
    EntityItem();
    EntityItem(QVariant name, QVariant entity);

    ~EntityItem();

    QVariant data(int column) const;
    int columnCount() const;
    int childCount() const;

    EntityItem* child(int row);
    EntityItem* parentItem();
    int row() const;

    friend class EnrolledModel;
    friend class LectureTreeModel;
    friend class TeachingLoadModel;

protected:
    void appendChild(EntityItem *item);

private:
    QVariant name;
    QVariant entity;
    EntityItem *parent = nullptr;
    QList<EntityItem *> children;
};

#endif // ENTITYITEM_H
