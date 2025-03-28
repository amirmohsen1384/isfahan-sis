#include "include/data/student.h"
#include "include/errors/general.h"
#include "include/errors/resource.h"
#include "include/errors/education.h"

Student::Student(QObject *parent) : Person{parent} {}

Student::Student(float score, QObject *parent) : Student{parent}
{
    setScore(score);
}

Student::Student(const Student &another, QObject *parent) : Student{parent}
{
    *this = another;
}

Student& Student::operator=(const Student &another)
{
    static_cast<Person&>(*this) = static_cast<const Person&>(another);
    score = another.score;
    return *this;
}

void Student::commitToRecord() const
{
    if(isNull()) {
        return;
    }

    QFile file(Student::getStudentFileName(*this));
    if(!file.open(QFile::WriteOnly)) {
        return;
    }

    QDataStream stream(&file);
    if((stream << *this).status() != QDataStream::Ok) {
        throw WriteFileException();
    }
}

Student Student::loadFromRecord(const Entity &value)
{
    if(value.isNull()) {
        return Student();
    }

    QFile file(Student::getStudentFileName(value));
    if(!file.open(QFile::ReadOnly)) {
        return Student();
    }
    QDataStream stream(&file);

    Student target;
    stream >> target;

    return target;
}

void Student::setIdentifier(const qint64 &value)
{
    QFileInfoList entries = Student::getStudentFiles();
    for(QFileInfo entry : entries) {
        if(entry.baseName().toLongLong() == value) {
            throw DuplicateEntityException();
        }
    }
    identifier = value;
    emit identifierChanged(value);
}

void Student::setScore(float value)
{
    if(value < 0) {
        score = 0;

    } else if(value > 20) {
        score = 20;

    } else {
        score = value;

    }
    emit scoreChanged(score);
}

float Student::getScore() const
{
    return score;
}

Student::State Student::getState() const
{
    if(score < 10) {
        return State::Rejection;

    } else if(score < 12 && score >= 10) {
        return State::Probation;

    } else if(score < 17 && score >= 12) {
        return State::Normal;

    } else if(score < 20 && score >= 17) {
        return State::Honor;

    } else {
        return State::Rejection;

    }
}

quint8 Student::getMinimumCredits() const
{
    const quint8 minimum = 12;
    return minimum;
}

quint8 Student::getMaximumCredits() const
{
    quint8 maximum = 0;
    switch(getState()) {
        case State::Probation: {
            maximum = 14;
            break;
        }
        case State::Normal: {
            maximum = 20;
            break;
        }
        case State::Honor: {
            maximum = 24;
            break;
        }
        default: {
            maximum = getMinimumCredits();
            break;
        }
    }
    return maximum;
}

void Student::addCredit(Lesson &lesson)
{
    if(!lesson.isAbleToEnroll()) {
        throw OutOfCapacityException();
    }

    quint64 credits = 0;
    LessonList container = this->getLessons();

    for(const Lesson &l : container) {
        if(l.getFinalExam() == lesson.getFinalExam()) {
            throw OverlapException();
        }
        credits += l.getCreditUnit();
    }

    if(credits < getMinimumCredits() || credits > getMaximumCredits()) {
        throw CreditsOutOfBoundException();
    }

    lesson.addStudent(*this);
    lesson.commitToRecord();

    Person::addCredit(lesson);
}

void Student::removeCredit(Lesson &lesson)
{
    lesson.removeStudent(*this);
    lesson.commitToRecord();
    Person::removeCredit(lesson);
}

QDir Student::getStudentDirectory()
{
    QDir directory = Entity::getEntityDirectory();
    directory.mkdir("Students");
    directory.cd("Students");
    return directory;
}

QFileInfoList Student::getStudentFiles()
{
    return Student::getStudentDirectory().entryInfoList({"*.stf"}, QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name);
}

QDataStream& operator<<(QDataStream &stream, const Student &data)
{
    stream << static_cast<const Person&>(data);
    stream << data.score;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, Student &data)
{
    stream >> static_cast<Person&>(data);
    stream >> data.score;
    return stream;
}

StudentList Student::getExistingStudents()
{
    StudentList result;
    QFileInfoList entries = Student::getStudentFiles();

    for(QFileInfo entry : entries) {
        QFile file(entry.absoluteFilePath());
        if(!file.open(QFile::ReadOnly)) {
            continue;
        }

        Student student;
        QDataStream stream(&file);
        stream >> student;

        if(!student.isNull()) {
            result.append(student);
        }
    }

    return result;
}

QString Student::getStudentFileName(const Entity &entity)
{
    return Student::getStudentDirectory().absoluteFilePath(QString("%1.stf").arg(entity.getIdentifier()));
}
