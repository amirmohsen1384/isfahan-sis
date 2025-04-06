#include "include/errors/resource.h"
#include "include/data/student.h"
#include "include/data/teacher.h"
#include "include/data/lesson.h"

Lesson::Lesson(QObject *parent) : Entity{parent} {}
Lesson::Lesson(const Lesson &other, QObject *parent) : Lesson{parent}
{
    *this = other;
}

Lesson &Lesson::operator=(const Lesson &other)
{
    static_cast<Entity&>(*this) = static_cast<const Entity&>(other);
    setTotalCapacity(other.totalCapacity);
    setBranchNumber(other.branchNumber);
    waitingList = other.waitingList;
    setCreditUnit(other.creditUnit);
    setFinalExam(other.finalExam);
    setName(other.name);
    return *this;
}

bool Lesson::hasTeacher() const
{
    return !this->getTeacher().isNull();
}

quint64 Lesson::getBranchNumber() const
{
    return branchNumber;
}

quint8 Lesson::getTotalCapacity() const
{
    return totalCapacity;
}

QList<Student> Lesson::getEnrolledStudents() const
{
    StudentList container = Student::getEntities();
    StudentList result;
    for(const Student &s : container) {
        if(s.enrollsIn(*this)) {
            result.append(s);
        }
    }
    return result;
}

QList<Student> Lesson::getWaitingStudents() const
{
    StudentList container;
    for(const Entity &e : waitingList) {
        container.append(Student::loadFromRecord(e));
    }
    return container;
}

QDateTime Lesson::getFinalExam() const
{
    return finalExam;
}

Teacher Lesson::getTeacher() const
{
    TeacherList container = Teacher::getEntities();
    for(const Teacher &t : container) {
        if(t.teaches(*this)) {
            return t;
        }
    }
    return Teacher();
}

QString Lesson::getName() const
{
    return name;
}

void Lesson::setName(const QString &value)
{
    name = value;
    emit nameChanged(name);
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
    return totalCapacity - getEnrolledStudents().size();
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

QString Lesson::getFileName(const Entity &value)
{
    QDir root = Lesson::getRoot();
    return root.absoluteFilePath(QString("%1.lss").arg(value.getIdentifier()));
}

void Lesson::commitToRecord() const
{
    if(isNull()) {
        return;
    }
    QFile file(Lesson::getFileName(*this));
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
    if(value.isNull()) {
        return Lesson();
    }

    QFile file(getFileName(value));
    if(!file.open(QFile::ReadOnly)) {
        return Lesson();
    }

    Lesson target;
    QDataStream stream(&file);
    if((stream >> target).status() != QDataStream::Ok) {
        return Lesson();
    }

    return target;
}

int Lesson::getTotalCredit(const LessonList &container)
{
    int result = 0;
    for(const Lesson &target : container) {
        result += target.getCreditUnit();
    }
    return result;
}

int Lesson::getTotalCredit(const EntityList &container)
{
    int result = 0;
    for(const Entity &entity : container) {
        result += Lesson::loadFromRecord(entity).getCreditUnit();
    }
    return result;
}

LessonList Lesson::getEntities()
{
    LessonList result;
    QFileInfoList entries = Lesson::getFiles();

    for(QFileInfo entry : entries) {
        QFile file(entry.absoluteFilePath());
        if(!file.open(QFile::ReadOnly)) {
            continue;
        }

        Lesson lesson;

        QDataStream stream(&file);
        stream >> lesson;

        if(!lesson.isNull()) {
            result.append(lesson);
        }
    }

    return result;
}

QFileInfoList Lesson::getFiles()
{
    QDir root = Lesson::getRoot();
    QFileInfoList entries = root.entryInfoList(
        {"*.lss"},
        QDir::NoDotAndDotDot | QDir::AllEntries,
        QDir::Name
        );
    return entries;
}

QDir Lesson::getRoot()
{
    QDir directory = Entity::getRoot();
    directory.mkdir("Lessons");
    directory.cd("Lessons");
    return directory;
}

QDataStream &operator<<(QDataStream &stream, const Lesson &data)
{
    stream << static_cast<const Entity&>(data);
    stream << data.totalCapacity;
    stream << data.branchNumber;
    stream << data.waitingList;
    stream << data.creditUnit;
    stream << data.finalExam;
    stream << data.name;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Lesson &data)
{
    stream >> static_cast<Entity&>(data);
    stream >> data.totalCapacity;
    stream >> data.branchNumber;
    stream >> data.waitingList;
    stream >> data.creditUnit;
    stream >> data.finalExam;
    stream >> data.name;
    return stream;
}
