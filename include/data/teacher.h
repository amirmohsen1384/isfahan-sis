#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include "lesson.h"

class Teacher : public Person
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);
    Teacher(const Teacher &another, QObject *parent = nullptr);
    Teacher& operator=(const Teacher &another);

    virtual void commitToRecord() const override;
    static Teacher loadFromRecord(const Entity &value);

    virtual void addCredit(Lesson &lesson) override;
    virtual void removeCredit(Lesson &lesson) override;

    friend QDataStream& operator<<(QDataStream &stream, const Teacher &data);
    friend QDataStream& operator>>(QDataStream &stream, Teacher &data);
};

QDataStream& operator<<(QDataStream &stream, const Teacher &data);
QDataStream& operator>>(QDataStream &stream, Teacher &data);

Q_DECLARE_METATYPE(Teacher)

#endif // TEACHER_H
