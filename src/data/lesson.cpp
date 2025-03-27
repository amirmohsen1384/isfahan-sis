#include "include/data/lesson.h"
#include "include/data/teacher.h"
#include "include/data/student.h"
#include "include/errors/resource.h"
#include "include/errors/education.h"

Lesson::Lesson(QObject *parent) : Entity{parent} {}
Lesson::Lesson(const Lesson &other, QObject *parent) : Lesson{parent}
{
    *this = other;
}

Lesson &Lesson::operator=(const Lesson &other)
{
    setTotalCapacity(other.totalCapacity);
    setBranchNumber(other.branchNumber);
    setCreditUnit(other.creditUnit);
    setFinalExam(other.finalExam);

    this->teacher = other.teacher;
    emit teacherChanged(teacher);

    enrolledStudents = other.enrolledStudents;
    emit enrolledStudentsChanged();
    return *this;
}

quint64 Lesson::getBranchNumber() const
{
    return branchNumber;
}

quint8 Lesson::getTotalCapacity() const
{
    return totalCapacity;
}

QDateTime Lesson::getFinalExam() const
{
    return finalExam;
}

Entity Lesson::getTeacher() const
{
    return teacher;
}

EntityList Lesson::getEnrolledStudents() const
{
    return enrolledStudents;
}

quint8 Lesson::getCreditUnit() const
{
    return creditUnit;
}

void Lesson::setCreditUnit(quint8 value)
{
    creditUnit = value;
    emit creditUnitChanged(value);
}

void Lesson::setBranchNumber(quint64 value)
{
    branchNumber = value;
    emit branchNumberChanged(value);
}

quint64 Lesson::getLeftCapacity() const
{
    return totalCapacity - enrolledStudents.size();
}

bool Lesson::isAbleToEnroll() const
{
    return this->getLeftCapacity() > 0;
}

void Lesson::setTotalCapacity(quint8 value)
{
    totalCapacity = value;
    emit totalCapacityChanged(value);
}

void Lesson::setFinalExam(const QDateTime &value)
{
    finalExam = value;
    emit finalExamChanged(value);
}

QString getLessonFileName(const Entity &value)
{
    QDir mainDirectory = Entity::getEntityDirectory();
    mainDirectory.mkdir("Lessons");
    mainDirectory.cd("Lessons");
    return mainDirectory.absoluteFilePath(QString("%1.lss").arg(value.getIdentifier()));
}

void Lesson::commitToRecord() const
{
    QFile file(getLessonFileName(*this));
    if(!file.open(QFile::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    if((stream << *this).status() != QDataStream::Ok) {
        throw WriteFileException();
    }
}

Lesson Lesson::loadFromRecord(const Entity &value)
{
    QFile file(getLessonFileName(value));
    if(!file.open(QFile::ReadOnly)) {
        return Lesson();
    }
    Lesson target;
    QDataStream stream(&file);
    if((stream >> target).status() != QDataStream::Ok) {
        throw ReadFileException();
    }
    return target;
}

void Lesson::setTeacher(const Teacher &value)
{
    this->teacher = static_cast<const Entity&>(value);
    emit teacherChanged(teacher);
}

void Lesson::addStudent(const Student &value)
{
    const auto count = value.getCreditCount();
    const auto minimum = value.getMinimumCredits();
    const auto maximum = value.getMaximumCredits();

    if(count < minimum || count > maximum) {
        throw CreditsOutOfBoundException();
    }

    if(!isAbleToEnroll()) {
        throw OutOfCapacityException();
    }

    QList<Lesson> lessons = value.getLessons();
    for(const Lesson &target : lessons) {
        if(target.getFinalExam() == getFinalExam()) {
            throw OverlapException();
        }
    }

    const Entity &entity = static_cast<const Entity&>(value);
    auto it = std::lower_bound(enrolledStudents.begin(), enrolledStudents.end(), entity);
    enrolledStudents.insert(std::distance(enrolledStudents.begin(), it), entity);
    emit enrolledStudentsChanged();
}

void Lesson::removeStudent(const Student &value)
{
    const Entity &entity = static_cast<const Entity&>(value);
    auto it = std::lower_bound(enrolledStudents.begin(), enrolledStudents.end(), entity);
    if(it != enrolledStudents.end() && *it == *this) {
        enrolledStudents.removeAt(std::distance(enrolledStudents.begin(), it));
        enrolledStudents.squeeze();
        emit enrolledStudentsChanged();
    }
}

QDataStream &operator<<(QDataStream &stream, const Lesson &data)
{
    stream << static_cast<const Entity&>(data);
    stream << data.enrolledStudents;
    stream << data.branchNumber;
    stream << data.totalCapacity;
    stream << data.finalExam;
    stream << data.teacher;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Lesson &data)
{
    stream >> static_cast<Entity&>(data);
    stream >> data.enrolledStudents;
    stream >> data.branchNumber;
    stream >> data.totalCapacity;
    stream >> data.finalExam;
    stream >> data.teacher;
    return stream;
}
