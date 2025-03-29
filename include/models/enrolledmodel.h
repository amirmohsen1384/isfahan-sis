#ifndef ENROLLEDMODEL_H
#define ENROLLEDMODEL_H

#include "enrolleditem.h"
#include <QFileSystemWatcher>
#include <QAbstractItemModel>
#include "include/data/lesson.h"
#include "include/data/student.h"
#include "include/data/teacher.h"

class EnrolledModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(EnrolledModel)
    explicit EnrolledModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    Teacher getTeacher() const;

public slots:
    void setTeacher(const Teacher &teacher);

signals:
    void teacherChanged(const Teacher &value);

protected:
    void resetModel();
    void updateInspector();
    void populateModel();

private:
    QFileSystemWatcher inspector;
    EnrolledItem *root = nullptr;
    Teacher target;
};

#endif // ENROLLEDMODEL_H
