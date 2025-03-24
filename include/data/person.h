#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);
    Person(const Person &person, QObject *parent = nullptr);

    Person& operator=(const Person &person);

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

    QString getUserName() const;
    void setUserName(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    quint64 getIdentifier() const;
    void setIdentifier(const quint64 &value);

    QPixmap getPhoto() const;
    void setPhoto(const QPixmap &value);

    friend QDataStream& operator<<(QDataStream &stream, const Person &data);
    friend QDataStream& operator>>(QDataStream &stream, Person &data);
    friend QDebug operator<<(QDebug debugger, const Person &data);

signals:
    void identifierChanged(const quint64 &identifier);
    void firstNameChanged(const QString &firstName);
    void lastNameChanged(const QString &lastName);
    void userNameChanged(const QString &userName);
    void passwordChanged(const QString &password);
    void photoChanged(const QPixmap &photo);

private:
    quint64     identifier;
    QString     firstName;
    QString     lastName;
    QString     userName;
    QString     password;
    QPixmap     photo;
};

QDataStream& operator<<(QDataStream &stream, const Person &data);
QDataStream& operator>>(QDataStream &stream, Person &data);

Q_DECLARE_METATYPE(Person)

#endif // PERSON_H
