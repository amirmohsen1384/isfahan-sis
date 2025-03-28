#ifndef LESSONLISTMODEL_H
#define LESSONLISTMODEL_H

#include <QFileSystemWatcher>
#include <QAbstractTableModel>
#include "include/data/lesson.h"

class LessonListModel : public QAbstractTableModel
{
    Q_OBJECT
    QFileSystemWatcher inspector;
public:
    explicit LessonListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected slots:
    void updateList();
    void updateInspector();

private:
    LessonList container;
};

#endif // LESSONLISTMODEL_H
