#ifndef ENROLLEDMODEL_H
#define ENROLLEDMODEL_H

#include "entityitem.h"
#include <QFileSystemWatcher>
#include <QAbstractItemModel>
#include "include/data/lesson.h"
#include "include/data/student.h"
#include "include/data/teacher.h"

class EnrolledModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit EnrolledModel(const Teacher &teacher, QObject *parent = nullptr);
    explicit EnrolledModel(QObject *parent = nullptr);
    Q_DISABLE_COPY_MOVE(EnrolledModel)
    ~EnrolledModel();

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
    void populateModel();
    void resetModel();

private:
    EntityItem *root = nullptr;
    Teacher target;
};

#endif // ENROLLEDMODEL_H
