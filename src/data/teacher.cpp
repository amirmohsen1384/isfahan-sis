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
    QFileInfoList entries = Teacher::getTeacherFiles();
    for(QFileInfo entry : entries) {
        if(entry.baseName().toLongLong() == value) {
            throw DuplicateEntityException();
        }
    }
    identifier = value;
    emit identifierChanged(value);
}

void Teacher::addCredit(Lesson &lesson)
{
    QList<Lesson> lessons = this->getLessons();
    for(const Lesson &target : lessons) {
        if(target.getFinalExam() == lesson.getFinalExam()) {
            throw OverlapException();
        }
    }

    lesson.teacher = static_cast<Entity>(*this);
    lesson.commitToRecord();
    Person::addCredit(lesson);
}

void Teacher::removeCredit(Lesson &lesson)
{
    EntityList students = lesson.enrolledStudents;
    for(const Entity &entity : students) {
        Student s = Student::loadFromRecord(entity);
        s.removeCredit(lesson);
        s.commitToRecord();
    }
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
        {"*.tcd"},
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
