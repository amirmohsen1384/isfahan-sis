#include "include/data/person.h"
#include "include/data/lesson.h"
#include <QDataStream>
#include <QDebug>
#include <QFile>

Person::Person(QObject *parent) : Entity{parent} {}

Person::Person(const Person &person, QObject *parent) : Person{parent}
{
    *this = person;
}

Person &Person::operator=(const Person &person)
{
    static_cast<Entity&>(*this) = static_cast<const Entity&>(person);
    this->lessons = person.lessons;
    setFirstName(person.firstName);
    setLastName(person.lastName);
    setUserName(person.userName);
    setPassword(person.password);
    setPhoto(person.photo);
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

QPixmap Person::getPhoto() const
{
    return photo;
}
void Person::setPhoto(const QPixmap &value)
{
    photo = value;
    emit photoChanged(photo);
}

void Person::addCredit(Lesson &lesson)
{
    Entity &entity = static_cast<Entity&>(lesson);
    auto it = std::lower_bound(lessons.begin(), lessons.end(), entity);
    int index = std::distance(lessons.begin(), it);
    lessons.insert(index, entity);
    emit lessonChanged();
}

void Person::removeCredit(Lesson &lesson)
{
    Entity &entity = static_cast<Entity&>(lesson);
    auto it = std::lower_bound(lessons.begin(), lessons.end(), entity);
    if(it != lessons.end() && *it == lesson) {
        int index = std::distance(lessons.begin(), it);
        lessons.removeAt(index);
        lessons.squeeze();
        emit lessonChanged();
    }
}

quint64 Person::getCreditCount() const
{
    quint64 total = 0;
    for(const Entity &entity : lessons)
    {
        Lesson lesson = Lesson::loadFromRecord(entity);
        if(!lesson.isNull()) {
            total += lesson.getCreditUnit();
        }
    }
    return total;
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
    stream << data.photo;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, Person &data)
{
    stream >> static_cast<Entity&>(data);
    stream >> data.firstName >> data.lastName;
    stream >> data.userName >> data.password;
    stream >> data.lessons;
    stream >> data.photo;
    return stream;
}

QDebug operator<<(QDebug debugger, const Person &data)
{
    QDebug environment = debugger.noquote();
    environment << "Identifier:" << data.identifier << '\n';
    environment << "First name:" << data.firstName << '\n';
    environment << "Last name:" << data.lastName << '\n';
    environment << "User name:" << data.userName << '\n';
    environment << "Password:" << data.password << '\n';
    return debugger;
}
