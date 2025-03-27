#include <QDir>
#include "include/data/teacher.h"
#include "include/data/student.h"
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

Teacher::~Teacher()
{
    commitToRecord();
}

QString getTeacherFileName(const Entity &value)
{
    QDir mainDirectory = Entity::getEntityDirectory();
    mainDirectory.mkdir("Teachers");
    mainDirectory.cd("Teachers");
    return mainDirectory.absoluteFilePath(QString("%1.tch").arg(value.getIdentifier()));
}

Teacher Teacher::loadFromRecord(const Entity &value)
{
    QFile file(getTeacherFileName(value));
    if(!file.open(QFile::ReadOnly)) {
        return Teacher();
    }
    QDataStream stream(&file);

    Teacher target;
    stream >> target;

    return target;
}

QString getLessonFileName(const Entity &value);

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

    const QString &name = getLessonFileName(lesson);
    QFile file(name);
    file.remove();
    file.close();

    Person::removeCredit(lesson);
}

void Teacher::commitToRecord() const
{
    const QString fileName = getTeacherFileName(*this);
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream << *this;
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
