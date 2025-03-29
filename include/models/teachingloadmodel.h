#ifndef TEACHINGLOADMODEL_H
#define TEACHINGLOADMODEL_H

#include "entityitem.h"
#include <QAbstractItemModel>

class TeachingLoadModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TeachingLoadModel(QObject *parent = nullptr);
    ~TeachingLoadModel();

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected:
    void populateModel();
    void resetModel();

private:
    EntityItem *root = nullptr;
};

#endif // TEACHINGLOADMODEL_H
