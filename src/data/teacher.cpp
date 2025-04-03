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

QString Teacher::getFileName(const Entity &value)
{
    return getRoot().absoluteFilePath(QString("%1.tch").arg(value.getIdentifier()));
}

Teacher Teacher::loadFromRecord(const Entity &value)
{
    if(value.isNull()) {
        return Teacher();
    }

    QFile file(Teacher::getFileName(value));
    if(!file.open(QFile::ReadOnly)) {
        return Teacher();
    }
    QDataStream stream(&file);

    Teacher target;
    if((stream >> target).status() != QDataStream::Ok) {
        return Teacher();
    }

    return target;
}

bool Teacher::teaches(const Lesson &target) const
{
    return std::binary_search(lessons.cbegin(), lessons.cend(), target);
}

void Teacher::addCredit(Lesson &target)
{
    if(target.isNull() || teaches(target)) {
        return;
    }
    auto it = std::lower_bound(lessons.begin(), lessons.end(), target);
    int index = std::distance(lessons.begin(), it);
    lessons.insert(index, target);
    emit lessonChanged();
}

void Teacher::removeCredit(Lesson &target)
{
    if(target.isNull() || !teaches(target)) {
        return;
    }

    auto it = std::lower_bound(lessons.begin(), lessons.end(), target);
    int index = std::distance(lessons.begin(), it);
    lessons.removeAt(index);
    lessons.squeeze();

    StudentList container = target.getEnrolledStudents();
    for(Student &s : container) {
        s.removeCredit(target);
        s.commitToRecord();
    }

    QFile::remove(Lesson::getFileName(target));

    emit lessonChanged();
}

QDir Teacher::getRoot()
{
    QDir directory = Entity::getRoot();
    directory.mkdir("Teachers");
    directory.cd("Teachers");
    return directory;
}

QFileInfoList Teacher::getFiles()
{
    QFileInfoList entries = Teacher::getRoot().entryInfoList({"*.tch"}, QDir::AllEntries | QDir::NoDotAndDotDot, QDir::SortFlag::Name);
    return entries;
}

TeacherList Teacher::getEntities()
{
    TeacherList result;
    QFileInfoList entries = Teacher::getFiles();

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

    QFile file(getFileName(*this));
    if(!file.open(QFile::WriteOnly)) {
        return;
    }

    QDataStream stream(&file);
    if((stream << *this).status() != QDataStream::Ok) {
        return;
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
