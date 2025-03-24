#include "include/data/person.h"
#include <QDebug>

Person::Person(const Person &person, QObject *parent) : Person{parent}
{
    *this = person;
}
Person::Person(QObject *parent) : QObject{parent} {}
Person &Person::operator=(const Person &person)
{
    this->identifier = person.identifier;
    this->firstName = person.firstName;
    this->lastName = person.lastName;
    this->userName = person.userName;
    this->password = person.password;
    this->photo = person.photo;
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
QString Person::setLastName(const QString &value)
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

quint64 Person::getIdentifier() const
{
    return identifier;
}
void Person::setIdentifier(const quint64 &value)
{
    identifier = value;
    emit identifierChanged(identifier);
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

QDataStream& operator<<(QDataStream &stream, const Person &data)
{
    stream << data.firstName << data.lastName;
    stream << data.userName << data.password;
    stream << data.identifier << data.photo;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, Person &data)
{
    stream >> data.firstName >> data.lastName;
    stream >> data.userName >> data.password;
    stream >> data.identifier >> data.photo;
    return stream;
}

QDebug operator<<(QDebug debugger, const Person &data)
{
    QDebug environment = debugger.noquote();
    environment << "Identifier:" << data.identifier;
    environment << "First name:" << data.firstName;
    environment << "Last name:" << data.lastName;
    environment << "User name:" << data.userName;
    environment << "Password:" << data.password;
    return debugger;
}
