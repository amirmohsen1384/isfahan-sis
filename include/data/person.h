#ifndef PERSON_H
#define PERSON_H

#include "lesson.h"
#include <QPixmap>

class Person : public Entity
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);
    Person(const Person &person, QObject *parent = nullptr);

    Person& operator=(const Person &person);

    QString getFirstName() const;

    QString getLastName() const;

    QString getUserName() const;

    QString getPassword() const;

    virtual LessonList getLessons() const;

    virtual quint64 getCreditCount() const;

    QString getFullName() const;

public slots:
    void setFirstName(const QString &value);

    void setLastName(const QString &value);

    void setUserName(const QString &value);

    void setPassword(const QString &value);

    virtual void addCredit(Lesson &lesson);

    virtual void removeCredit(Lesson &lesson);

    friend QDataStream& operator<<(QDataStream &stream, const Person &data);
    friend QDataStream& operator>>(QDataStream &stream, Person &data);
    friend QDebug operator<<(QDebug debugger, const Person &data);

signals:
    void firstNameChanged(const QString &firstName);
    void lastNameChanged(const QString &lastName);
    void userNameChanged(const QString &userName);
    void passwordChanged(const QString &password);
    void lessonChanged();

protected:
    QString     firstName;
    QString     lastName;
    QString     userName;
    QString     password;
    EntityList  lessons;
};

QDataStream& operator<<(QDataStream &stream, const Person &data);
QDataStream& operator>>(QDataStream &stream, Person &data);

Q_DECLARE_METATYPE(Person)

#endif // PERSON_H
