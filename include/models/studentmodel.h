#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include <QAbstractTableModel>
#include "include/data/student.h"

class StudentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit StudentModel(const Student &data, QObject *parent = nullptr);
    explicit StudentModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Student& container();

public slots:
    void refresh();

private:
    Student container;
};

#endif // STUDENTMODEL_H
