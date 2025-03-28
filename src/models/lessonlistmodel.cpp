#include "include/models/lessonlistmodel.h"
#include "include/data/teacher.h"

LessonListModel::LessonListModel(QObject *parent) : QAbstractTableModel(parent)
{
    updateList();
    updateInspector();
    inspector.addPath(Lesson::getLessonsDirectory().absolutePath());
    connect(&inspector, &QFileSystemWatcher::fileChanged, this, &LessonListModel::updateList);
    connect(&inspector, &QFileSystemWatcher::directoryChanged, this, &LessonListModel::updateList);
    connect(&inspector, &QFileSystemWatcher::directoryChanged, this, &LessonListModel::updateInspector);
}

int LessonListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return container.size();
}

int LessonListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return 5;
}

QVariant LessonListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const Lesson &lesson = container.at(index.row());
    if(role == Qt::UserRole) {
        return QVariant::fromValue(lesson);

    }

    else if(role != Qt::DisplayRole) {
        return QVariant();

    }

    switch(index.column()) {
    case 0: {
        const QString &name = lesson.getName();
        return (!name.isEmpty() ? name : "Unnamed Lesson");
    }
    case 1: {
        return lesson.getIdentifier();
    }
    case 2: {
        const QString &name = lesson.getTeacher().getFullName();
        return (!name.isEmpty() ? name : "Unknown Teacher");
    }
    case 3: {
        return lesson.getBranchNumber();
    }
    case 4: {
        return lesson.getLeftCapacity();
    }
    default: {
        return QVariant();
    }
    }
}

QVariant LessonListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Horizontal) {
        switch(section) {
        case 0: {
            return "Name";
        }
        case 1: {
            return "ID Number";
        }
        case 2: {
            return "Teacher's Name";
        }
        case 3: {
            return "Branch Number";
        }
        case 4: {
            return "Remaining Capacity";
        }
        default: {
            return QVariant();
        }
        }
    }

    else {
        return section + 1;
    }
}

void LessonListModel::updateList()
{
    beginResetModel();
    container = Lesson::getExistingLessons();
    endResetModel();
}

void LessonListModel::updateInspector()
{
    if(!inspector.files().isEmpty()) {
        inspector.removePaths(inspector.files());
    }
    QFileInfoList entries = Lesson::getLessonFiles();
    for(QFileInfo entry : entries) {
        inspector.addPath(entry.absoluteFilePath());
    }
}
