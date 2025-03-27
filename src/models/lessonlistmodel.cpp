#include "include/models/lessonlistmodel.h"
#include "include/data/teacher.h"

LessonListModel::LessonListModel(QObject *parent) : QAbstractTableModel(parent)
{
    QDir directory = Entity::getEntityDirectory();
    if(directory.cd("Lessons")) {
        inspector.addPath(directory.absolutePath());
        connect(&inspector, &QFileSystemWatcher::directoryChanged, this, &LessonListModel::updateList);
    }
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

    } else if(role != Qt::DisplayRole) {
        return QVariant();

    }

    switch(index.column()) {
    case 0: {
        const QString &name = lesson.getName();
        return name;
    }
    case 1: {
        const quint64 identifier = lesson.getIdentifier();
        return identifier;
    }
    case 2: {
        const QString name = Teacher::loadFromRecord(lesson.getTeacher()).getFullName();
        return name;
    }
    case 3: {
        const quint64 number = lesson.getBranchNumber();
        return number;
    }
    case 4: {
        const quint64 remaining = lesson.getLeftCapacity();
        return remaining;
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

    else if(orientation == Qt::Vertical) {
        return section + 1;
    }
}

void LessonListModel::updateList()
{
    beginResetModel();
    container = Lesson::getExistingLessons();
    endResetModel();
}
