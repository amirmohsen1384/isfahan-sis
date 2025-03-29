#ifndef ENROLLEDITEM_H
#define ENROLLEDITEM_H

#include "include/data/entity.h"
#include <QVariant>

class EnrolledItem
{
public:
    EnrolledItem();
    EnrolledItem(QVariant name, QVariant entity);

    ~EnrolledItem();

    QVariant data(int column) const;
    int columnCount() const;
    int childCount() const;

    EnrolledItem* child(int row);
    EnrolledItem* parentItem();
    int row() const;

    friend class EnrolledModel;

private:
    QVariant name;
    QVariant entity;
    EnrolledItem *parent = nullptr;
    QList<EnrolledItem *> children;
};

#endif // ENROLLEDITEM_H
