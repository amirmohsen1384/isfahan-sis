#ifndef LECTURETREEMODEL_H
#define LECTURETREEMODEL_H

#include <QAbstractItemModel>
#include "include/models/entityitem.h"

class LectureTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(LectureTreeModel)
    explicit LectureTreeModel(QObject *parent = nullptr);
    ~LectureTreeModel();

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;

protected slots:
    virtual void setupModel() = 0;
    virtual void resetModel();

protected:
    EntityItem *root = nullptr;
};

#endif // LECTURETREEMODEL_H
