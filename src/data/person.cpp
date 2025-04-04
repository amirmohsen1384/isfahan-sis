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
    setFirstName(person.firstName);
    setLastName(person.lastName);
    setUserName(person.userName);
    setPassword(person.password);
    lessons = person.lessons;
    emit lessonChanged();
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
        total += target.getCreditUnit();
    }
    return total;
}

QString Person::getFullName() const
{
    QString target;
    if(firstName.isEmpty() && !lastName.isEmpty()) {
        target = QString("%1").arg(lastName);
    }
    else {
        target.append(firstName);
        if(!lastName.isEmpty()) {
            target.append(QString(" %2").arg(lastName));
        }
    }
    return target;
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
