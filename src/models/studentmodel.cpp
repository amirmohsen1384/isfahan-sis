#include "include/models/studentmodel.h"
#include "include/data/teacher.h"

#define NAME_COLUMN 0
#define ID_COLUMN 1
#define TEACHER_COLUMN 2
#define BRANCH_COLUMN 3
#define STATUS_COLUMN 4
#define CAPACITY_COLUMN 5

StudentModel::StudentModel(const Student &data, QObject *parent) : StudentModel(parent)
{
    container = data;
    refresh();
}

StudentModel::StudentModel(QObject *parent) : QAbstractTableModel(parent)
{
    connect(&container, &Student::lessonChanged, this, &StudentModel::refresh);
    connect(&container, &Student::lessonQueueChanged, this, &StudentModel::refresh);
}

QVariant StudentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole) {
        return {};
    }
    switch(orientation) {
    case Qt::Horizontal: {
        switch(section) {
        case NAME_COLUMN: {
            return "Name";
        }
        case ID_COLUMN: {
            return "ID Number";
        }
        case TEACHER_COLUMN: {
            return "Teacher";
        }
        case BRANCH_COLUMN: {
            return "Branch Number";
        }
        case STATUS_COLUMN: {
            return "Status";
        }
        case CAPACITY_COLUMN: {
            return "Capacity";
        }
        default: {
            return {};
        }
        }
        break;
    }
    case Qt::Vertical: {
        return section + 1;
        break;
    }
    default: {
        return {};
    }
    }
}

Student &StudentModel::getContainer()
{
    return container;
}

void StudentModel::refresh()
{
    beginResetModel();
    endResetModel();
}

int StudentModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 0;
    }
    return 6;
}
int StudentModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 0;
    }
    return container.getLessons().size() + container.getWaitingLessons().size();
}

QVariant StudentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    LessonList waiting = container.getWaitingLessons();
    LessonList resource = container.getLessons();

    if(role == Qt::BackgroundRole) {
        if(index.column() != STATUS_COLUMN) {
            return {};
        }

        int row = index.row();
        if(row >= 0 && row < resource.size()) {
            // light green
            return QColor(200, 250, 180);
        }

        row -= resource.size();
        if(row >= 0 && row < waiting.size()) {
            // light red
            return QColor(255, 160, 160);
        }

        return {};
    }
    else if(role != Qt::UserRole) {
        int row = index.row();
        if(row >= 0 && row < resource.size()) {
            return QVariant::fromValue(resource.at(row));
        }

        row -= resource.size();
        if(row >= 0 && row < waiting.size()) {
            return QVariant::fromValue(waiting.at(row));
        }
    }
    else if(role != Qt::DisplayRole) {
        return {};
    }

    Lesson target;
    int row = index.row();
    if(row >= 0 && row < resource.size()) {
        target = resource.at(row);
        if(index.column() == STATUS_COLUMN) {
            return "Registered";
        }
    }

    row -= resource.size();
    if(row >= 0 && row < waiting.size()) {
        target = waiting.at(row);
        if(index.column() == STATUS_COLUMN) {
            return "In Queue";
        }

    } else {
        return {};
    }

    switch(index.column()) {
    case NAME_COLUMN: {
        return target.getName();
        break;
    }
    case ID_COLUMN: {
        return target.getIdentifier();
        break;
    }
    case TEACHER_COLUMN: {
        return target.getTeacher().getFullName();
        break;
    }
    case BRANCH_COLUMN: {
        return target.getBranchNumber();
        break;
    }
    case CAPACITY_COLUMN: {
        return target.getLeftCapacity();
        break;
    }
    default: {
        return {};
        break;
    }
    }
}
