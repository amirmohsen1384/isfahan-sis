#include "include/data/lesson.h"
#include "include/data/teacher.h"
#include "include/data/student.h"
#include "include/errors/general.h"
#include "include/errors/resource.h"
#include "include/errors/education.h"

Lesson::Lesson(QObject *parent) : Entity{parent} {}
Lesson::Lesson(const Lesson &other, QObject *parent) : Lesson{parent}
{
    *this = other;
}

Lesson &Lesson::operator=(const Lesson &other)
{
    static_cast<Entity&>(*this) = static_cast<const Entity&>(other);
    enrolledStudents = other.enrolledStudents;
    totalCapacity = other.totalCapacity;
    branchNumber = other.branchNumber;
    creditUnit = other.creditUnit;
    finalExam = other.finalExam;
    teacher = other.teacher;
    name = other.name;
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

Teacher Lesson::getTeacher() const
{
    return Teacher::loadFromRecord(teacher);
}

StudentList Lesson::getEnrolledStudents() const
{
    StudentList result;
    for(Entity s : enrolledStudents) {
        Student s = Student::loadFromRecord(s);
        if(!s.isNull()) {
            result.append(s);
        }
    }
    return result;
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

QString Lesson::getLessonFileName(const Entity &value)
{
    QDir root = Lesson::getLessonsDirectory();
    return root.absoluteFilePath(QString("%1.lss").arg(value.getIdentifier()));
}

void Lesson::commitToRecord() const
{
    if(isNull()) {
        return;
    }
    QFile file(Lesson::getLessonFileName(*this));
    if(!file.open(QFile::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    if((stream << *this).status() != QDataStream::Ok) {
        throw WriteFileException();
    }
}

void Lesson::setIdentifier(const qint64 &value)
{
    QFileInfoList entries = Lesson::getLessonFiles();
    for(QFileInfo entry : entries) {
        if(entry.baseName().toLongLong() == value) {
            throw DuplicateEntityException();
        }
    }

    QFile::remove(Lesson::getLessonFileName(*this));
    this->identifier = value;
    commitToRecord();

    emit identifierChanged(identifier);
}

Lesson Lesson::loadFromRecord(const Entity &value)
{
    if(value.isNull()) {
        return Lesson();
    }

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

LessonList Lesson::getExistingLessons()
{
    LessonList result;
    QFileInfoList entries = Lesson::getLessonFiles();

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

QFileInfoList Lesson::getLessonFiles()
{
    QDir root = Lesson::getLessonsDirectory();
    QFileInfoList entries = root.entryInfoList(
        {"*.lss"},
        QDir::NoDotAndDotDot | QDir::AllEntries,
        QDir::Name
        );
    return entries;
}

QDir Lesson::getLessonsDirectory()
{
    QDir directory = Entity::getEntityDirectory();
    directory.mkdir("Lessons");
    directory.cd("Lessons");
    return directory;
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
    stream << data.creditUnit;
    stream << data.totalCapacity;
    stream << data.finalExam;
    stream << data.teacher;
    stream << data.name;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Lesson &data)
{
    stream >> static_cast<Entity&>(data);
    stream >> data.enrolledStudents;
    stream >> data.branchNumber;
    stream >> data.creditUnit;
    stream >> data.totalCapacity;
    stream >> data.finalExam;
    stream >> data.teacher;
    stream >> data.name;
    return stream;
}
