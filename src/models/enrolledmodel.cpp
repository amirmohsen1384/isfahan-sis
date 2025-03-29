#include "include/models/enrolledmodel.h"

EnrolledModel::EnrolledModel(const Teacher &teacher, QObject *parent) : EnrolledModel(parent)
{
    setTeacher(teacher);
}

EnrolledModel::EnrolledModel(QObject *parent) : LectureTreeModel(parent)
{
    connect(this, &EnrolledModel::teacherChanged, this, &EnrolledModel::setupModel);
}

QVariant EnrolledModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return {};
    }
    else if(role == Qt::UserRole) {
        QModelIndex target = this->index(index.row(), 1, index.parent());
        Entity entity(target.data().toLongLong());
        if(index.parent().isValid()) {
            return QVariant::fromValue(Student::loadFromRecord(entity));
        }
        else {
            return QVariant::fromValue(Lesson::loadFromRecord(entity));
        }
    }
    else if(role != Qt::DisplayRole) {
        return {};
    }
    EntityItem *item = static_cast<EntityItem*>(index.internalPointer());
    return item->data(index.column());
}

Teacher EnrolledModel::getTeacher() const
{
    return target;
}

void EnrolledModel::setTeacher(const Teacher &teacher)
{
    target = teacher;
    emit teacherChanged(target);
}

void EnrolledModel::setupModel()
{
    beginResetModel();

    resetModel();
    root = new EntityItem("Name", "ID Number");

    LessonList lessons = target.getLessons();
    for(Lesson lesson : lessons) {
        EntityItem *parent = new EntityItem;

        parent->name = lesson.getName();
        parent->entity = lesson.getIdentifier();

        StudentList container = lesson.getEnrolledStudents();

        for(Student data : container) {
            EntityItem *child = new EntityItem;

            child->parent = parent;
            child->name = data.getFullName();
            child->entity = data.getIdentifier();

            parent->children.append(child);
        }

        root->children.append(parent);
    }

    endResetModel();
}
