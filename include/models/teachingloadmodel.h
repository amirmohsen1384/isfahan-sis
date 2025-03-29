#ifndef TEACHINGLOADMODEL_H
#define TEACHINGLOADMODEL_H

#include "core/entityitem.h"
#include <QAbstractItemModel>
#include "core/lecturetreemodel.h"

class TeachingLoadModel : public LectureTreeModel
{
    Q_OBJECT

public:
    explicit TeachingLoadModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    virtual void setupModel() override;
};

#endif // TEACHINGLOADMODEL_H
