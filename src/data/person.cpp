#include "include/data/person.h"
#include "include/data/lesson.h"
#include <QDataStream>
#include <QFile>

Person::Person(QObject *parent) : Entity{parent} {}

Person::Person(const Person &person, QObject *parent) : Person{parent}
{
    *this = person;
}

Person &Person::operator=(const Person &person)
{
    static_cast<Entity&>(*this) = static_cast<const Entity&>(person);
    firstName = person.firstName;
    userName = person.userName;
    password = person.password;
    lastName = person.lastName;
    lessons = person.lessons;
    return *this;
}

QString Person::getFirstName() const
{
    return firstName;
}
void Person::setFirstName(const QString &value)
{
    firstName = value;
    emit firstNameChanged(firstName);
}

QString Person::getLastName() const
{
    return lastName;
}
void Person::setLastName(const QString &value)
{
    lastName = value;
    emit lastNameChanged(lastName);
}

QString Person::getUserName() const
{
    return userName;
}
void Person::setUserName(const QString &value)
{
    userName = value;
    emit userNameChanged(userName);
}

QString Person::getPassword() const
{
    return password;
}
void Person::setPassword(const QString &value)
{
    password = value;
    emit passwordChanged(password);
}

quint64 Person::getCreditCount() const
{
    quint64 total = 0;
    LessonList container = this->getLessons();
    for(const Lesson &target : container)
    {
        total += lesson.getCreditUnit();
    }
    return total;
}

QString Person::getFullName() const
{
    return QString("%1 %2").arg(firstName).arg(lastName);
}

LessonList Person::getLessons() const
{
    QList<Lesson> container;
    for(const Entity &entity : lessons) {
        Lesson lesson = Lesson::loadFromRecord(entity);
        if(!lesson.isNull()) {
            container.append(lesson);
        }
    }
    return container;
}

QDataStream& operator<<(QDataStream &stream, const Person &data)
{
    stream << static_cast<const Entity&>(data);
    stream << data.firstName << data.lastName;
    stream << data.userName << data.password;
    stream << data.lessons;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, Person &data)
{
    stream >> static_cast<Entity&>(data);
    stream >> data.firstName >> data.lastName;
    stream >> data.userName >> data.password;
    stream >> data.lessons;
    return stream;
}
