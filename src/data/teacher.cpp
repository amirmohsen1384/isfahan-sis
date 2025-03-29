#include "include/data/teacher.h"
#include "include/data/student.h"
#include "include/errors/resource.h"
#include "include/errors/education.h"

Teacher::Teacher(QObject *parent) : Person{parent} {}

Teacher::Teacher(const Teacher &another, QObject *parent) : Teacher{parent}
{
    *this = another;
}

Teacher& Teacher::operator=(const Teacher &another)
{
    static_cast<Person&>(*this) = static_cast<const Person&>(another);
    return *this;
}

QString Teacher::getTeacherFileName(const Entity &value)
{
    return getTeacherDirectory().absoluteFilePath(QString("%1.tch").arg(value.getIdentifier()));
}

Teacher Teacher::loadFromRecord(const Entity &value)
{
    if(value.isNull()) {
        return Teacher();
    }

    QFile file(Teacher::getTeacherFileName(value));
    if(!file.open(QFile::ReadOnly)) {
        return Teacher();
    }
    QDataStream stream(&file);

    Teacher target;
    stream >> target;

    return target;
}

void Teacher::setIdentifier(const qint64 &value)
{
    if(QFile::exists(Teacher::getTeacherFileName(Entity(value)))) {
        return;
    }

    QFile::remove(Teacher::getTeacherFileName(*this));
    identifier = value;
    commitToRecord();

    emit identifierChanged(value);
}

void Teacher::addCredit(Lesson &lesson)
{
    // Checks if the lesson is null
    if(lesson.isNull()) {
        return;
    }

    // Converts the lessons into an entity
    Entity &entity = static_cast<Entity&>(lesson);

    // Searchs for the lesson in the container
    auto it = std::lower_bound(lessons.begin(), lessons.end(), entity);

    // If there's no target matching the lesson
    if(it == lessons.end() || *it != entity) {

        // Checks for time overlapping
        LessonList container = getLessons();
        for(Lesson temp : container) {
            if(temp.getFinalExam() == lesson.getFinalExam()) {
                throw OverlapException();
            }
        }

        // Assign the teacher to the lesson
        lesson.setTeacher(*this);
        lesson.commitToRecord();

        // Inserts the lesson to the list
        int index = std::distance(lessons.begin(), it);
        lessons.insert(index, entity);

        emit lessonChanged();
    }
}

void Teacher::removeCredit(Lesson &lesson)
{
    // Checks if the lesson is null
    if(lesson.isNull()) {
        return;
    }

    // Removes the lesson from the credits of enrolled students
    StudentList students = lesson.getEnrolledStudents();
    for(Student &target : students) {
        target.removeCredit(lesson);
        target.commitToRecord();
    }

    // Removes the lesson file from the disk and the list.
    QFile::remove(Lesson::getLessonFileName(lesson));
    Person::removeCredit(lesson);
}

QDir Teacher::getTeacherDirectory()
{
    QDir directory = Entity::getEntityDirectory();
    directory.mkdir("Teachers");
    directory.cd("Teachers");
    return directory;
}

QFileInfoList Teacher::getTeacherFiles()
{
    QFileInfoList entries = Teacher::getTeacherDirectory().entryInfoList(
        {"*.tch"},
        QDir::AllEntries | QDir::NoDotAndDotDot,
        QDir::SortFlag::Name
    );
    return entries;
}

TeacherList Teacher::getExistingTeachers()
{
    TeacherList result;
    QFileInfoList entries = Teacher::getTeacherFiles();

    for(QFileInfo entry : entries) {
        QFile file(entry.absoluteFilePath());
        if(!file.open(QFile::ReadOnly)) {
            continue;
        }

        Teacher teacher;
        QDataStream stream(&file);
        if((stream >> teacher).status() != QDataStream::Ok) {
            continue;
        }

        if(!teacher.isNull()) {
            result.append(teacher);
        }
    }

    return result;
}

void Teacher::commitToRecord() const
{
    if(isNull()) {
        return;
    }

    QFile file(getTeacherFileName(*this));
    if(!file.open(QFile::WriteOnly)) {
        return;
    }

    QDataStream stream(&file);
    if((stream << *this).status() != QDataStream::Ok) {
        throw WriteFileException();
    }

    return;
}

QDataStream& operator<<(QDataStream &stream, const Teacher &data)
{
    stream << static_cast<const Person&>(data);
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Teacher &data)
{
    stream >> static_cast<Person&>(data);
    return stream;
}
