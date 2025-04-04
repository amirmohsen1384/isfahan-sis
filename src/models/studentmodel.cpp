#include "include/models/studentmodel.h"

StudentModel::StudentModel(const Student &data, QObject *parent) : StudentModel(parent)
{
    container = data;
}

StudentModel::StudentModel(QObject *parent) : QAbstractTableModel(parent)
{
    connect(&container, &Student::lessonChanged, this, &StudentModel::refresh);
    connect(&container, &Student::lessonQueueChanged, this, &StudentModel::refresh);
}

Student &StudentModel::container()
{
    return container;
}

void StudentModel::refresh()
{
    beginResetModel();

    endResetModel();
}

int StudentModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int StudentModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant StudentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
