#ifndef PERSON_H
#define PERSON_H

#include "lesson.h"
#include <QPixmap>

class Person : public Entity
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr) : Entity{parent} {}
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

    QPixmap getPhoto() const;
    void setPhoto(const QPixmap &value);

    virtual void addCredit(Lesson &lesson);
    virtual void removeCredit(Lesson &lesson);

    virtual QList<Lesson> getLessons() const;
    virtual quint64 getCreditCount() const;

    friend QDataStream& operator<<(QDataStream &stream, const Person &data);
    friend QDataStream& operator>>(QDataStream &stream, Person &data);
    friend QDebug operator<<(QDebug debugger, const Person &data);

signals:
    void firstNameChanged(const QString &firstName);
    void lastNameChanged(const QString &lastName);
    void userNameChanged(const QString &userName);
    void passwordChanged(const QString &password);
    void photoChanged(const QPixmap &photo);
    void lessonRemoved();
    void lessonAdded();

protected:
    QString     firstName;
    QString     lastName;
    QString     userName;
    QString     password;
    EntityList  lessons;
    QPixmap     photo;
};

QDataStream& operator<<(QDataStream &stream, const Person &data);
QDataStream& operator>>(QDataStream &stream, Person &data);

Q_DECLARE_METATYPE(Person)

#endif // PERSON_H
