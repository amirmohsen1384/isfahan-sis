#include "include/models/enrolledmodel.h"

EnrolledModel::EnrolledModel(const Teacher &teacher, QObject *parent) : EnrolledModel(parent)
{
    setTeacher(teacher);
}

EnrolledModel::EnrolledModel(QObject *parent) : LectureTreeModel(parent)
{
    setupModel();
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

        Student student = Student::loadFromRecord(entity);
        if(student.isNull()) {
            Lesson lesson = Lesson::loadFromRecord(entity);
            if(lesson.isNull()) {
                return {};
            }
            else {
                return QVariant::fromValue(lesson);
            }
        } else {
            return QVariant::fromValue(student);
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
        EntityItem *parent = new EntityItem(lesson.getName(), lesson.getIdentifier());

        StudentList container = lesson.getEnrolledStudents();
        for(Student data : container) {
            EntityItem *child = new EntityItem(data.getFullName(), data.getIdentifier());
            parent->appendChild(child);
        }

        root->appendChild(parent);
    }

    endResetModel();
}
