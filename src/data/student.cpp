#include "include/data/student.h"
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

    QFile file(Student::getFileName(*this));
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

    QFile file(Student::getFileName(value));
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
    if(QFile::exists(Student::getFileName(Entity(value)))) {
        return;
    }

    QFile::remove(Student::getFileName(*this));
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
    // Converts the lesson into its entity
    Entity &entity = static_cast<Entity&>(lesson);

    // Searchs for the lesson in the list
    auto it = std::lower_bound(lessons.begin(), lessons.end(), entity);

    // If there's no item matching the lesson
    if(it == lessons.end() || *it != entity) {

        // Checks for the ability to enroll.
        if(!lesson.isAbleToEnroll()) {
            throw OutOfCapacityException();
        }

        // Checks for the bounds of credits and time overlapping
        LessonList container = this->getLessons();
        quint64 credits = 0;

        for(const Lesson &temp : container) {
            if(temp.getFinalExam() == lesson.getFinalExam()) {
                throw OverlapException();
            }
            credits += temp.getCreditUnit();
        }

        // Inserts the student into the lesson's list.
        lesson.addStudent(*this);
        lesson.commitToRecord();

        // Inserts the lesson into the student's list.
        int index = std::distance(lessons.begin(), it);
        lessons.insert(index, entity);

        emit lessonChanged();
    }
}

void Student::removeCredit(Lesson &lesson)
{
    lesson.removeStudent(*this);
    lesson.commitToRecord();
    Person::removeCredit(lesson);
}

QDir Student::getRoot()
{
    QDir directory = Entity::getRoot();
    directory.mkdir("Students");
    directory.cd("Students");
    return directory;
}

QFileInfoList Student::getFiles()
{
    return Student::getRoot().entryInfoList({"*.stf"}, QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name);
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

StudentList Student::getEntities()
{
    StudentList result;
    QFileInfoList entries = Student::getFiles();

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

QString Student::getFileName(const Entity &entity)
{
    return Student::getRoot().absoluteFilePath(QString("%1.stf").arg(entity.getIdentifier()));
}
