#include "include/data/student.h"
#include "include/errors/education.h"

QString getStudentFileName(const Entity &value)
{
    QDir mainDirectory = Entity::getEntityDirectory();
    mainDirectory.mkdir("Students");
    mainDirectory.cd("Students");
    return mainDirectory.absoluteFilePath(QString("%1.stf").arg(value.getIdentifier()));
}

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
    this->score = another.score;
    return *this;
}

Student::~Student()
{
    commitToRecord();
}

void Student::commitToRecord() const
{
    QFile file(getStudentFileName(*this));
    if(!file.open(QFile::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream << *this;
    return;
}

Student Student::loadFromRecord(const Entity &value)
{
    QFile file(getStudentFileName(value));
    if(!file.open(QFile::ReadOnly)) {
        return Student();
    }
    QDataStream stream(&file);

    Student target;
    stream >> target;

    return target;
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
    QDir directory = Entity::getEntityDirectory();
    if(!directory.cd("Students")) {
        return StudentList();
    }

    QFileInfoList entries = directory.entryInfoList(
        {"*.stf"},
        QDir::AllEntries | QDir::NoDotAndDotDot,
        QDir::SortFlag::Name
    );

    StudentList result;
    for(QFileInfo entry : entries) {
        QFile file(entry.absoluteFilePath());
        if(!file.open(QFile::ReadOnly)) {
            continue;
        }

        Student student;
        QDataStream stream(&file);
        stream >> student;
        result.append(student);
    }

    return result;
}
