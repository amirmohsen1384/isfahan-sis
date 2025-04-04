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
    setScore(another.score);
    queue = another.queue;
    emit lessonQueueChanged();
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
        return;
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

    Student target;
    QDataStream stream(&file);
    if((stream >> target).status() != QDataStream::Ok) {
        return Student();
    }

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

bool Student::enrollsIn(const Lesson &target) const
{
    return std::binary_search(lessons.cbegin(), lessons.cend(), target);
}

LessonList Student::getWaitingLessons() const
{
    LessonList container;
    for(const Entity &entity : queue) {
        Lesson l = Lesson::loadFromRecord(entity);
        if(!l.isNull()) {
            container.append(l);
        }
    }
    return container;
}

void Student::addCredit(Lesson &target)
{
    if(enrollsIn(target) || target.isNull()) {
        return;
    }

    if(!target.isAbleToEnroll()) {
        target.waitingList.enqueue(*this);
        target.commitToRecord();
        queue.enqueue(target);
        emit lessonQueueChanged();
        return;

    } else {
        auto it = std::lower_bound(queue.begin(), queue.end(), target);
        if(it != queue.end() && *it == target) {
            int index = std::distance(queue.begin(), it);
            queue.removeAt(index);
            queue.squeeze();
            emit lessonQueueChanged();
        }
    }

    auto it = std::lower_bound(lessons.begin(), lessons.end(), target);
    int index = std::distance(lessons.begin(), it);
    lessons.insert(index, target);
    emit lessonChanged();
}

void Student::removeCredit(Lesson &target)
{
    if(target.isNull()) {
        return;
    }

    auto it = std::lower_bound(lessons.begin(), lessons.end(), target);
    if(it != lessons.end() && *it == target) {
        int index = std::distance(lessons.begin(), it);
        lessons.removeAt(index);
        lessons.squeeze();

        if(target.isAbleToEnroll() && !target.waitingList.isEmpty()) {
            Student s = Student::loadFromRecord(target.waitingList.dequeue());
            target.commitToRecord();
            s.addCredit(target);
            s.commitToRecord();
        }

        emit lessonChanged();
    }
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
    stream << data.queue;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, Student &data)
{
    stream >> static_cast<Person&>(data);
    stream >> data.score;
    stream >> data.queue;
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
        if((stream >> student).status() != QDataStream::Ok) {
            continue;
        }

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
