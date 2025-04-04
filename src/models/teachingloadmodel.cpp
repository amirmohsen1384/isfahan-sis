#include "include/models/teachingloadmodel.h"
#include "include/data/teacher.h"

TeachingLoadModel::TeachingLoadModel(QObject *parent) : LectureTreeModel(parent)
{
    setupModel();
}

QVariant TeachingLoadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }
    else if(role == Qt::UserRole) {
        QModelIndex target = this->index(index.row(), 1, index.parent());
        Entity entity(target.data(Qt::DisplayRole).toLongLong());
        if(!index.parent().isValid()) {
            return QVariant::fromValue(Teacher::loadFromRecord(entity));

        } else {
            return QVariant::fromValue(Lesson::loadFromRecord(entity));

        }
    }
    else if(role != Qt::DisplayRole) {
        return {};
    }
    return static_cast<EntityItem*>(index.internalPointer())->data(index.column());
}

void TeachingLoadModel::setupModel()
{
    beginResetModel();

    resetModel();
    root = new EntityItem("Name", "ID Number");

    TeacherList container = Teacher::getEntities();
    for(Teacher one : container) {
        EntityItem *parent = new EntityItem(one.getFullName(), one.getIdentifier());

        LessonList lectures = one.getLessons();
        for(Lesson lecture : lectures) {
            EntityItem *item = new EntityItem(lecture.getName(), lecture.getIdentifier());
            parent->appendChild(item);
        }

        root->children.append(parent);
    }

    endResetModel();
}
