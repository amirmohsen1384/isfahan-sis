#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

class Student : public Person
{
    Q_OBJECT
public:
    enum class State {Rejection, Probation, Normal, Honor}; Q_ENUM(State)

public:
    explicit Student(QObject *parent = nullptr);
    Student(float score, QObject *parent = nullptr);
    Student(const Student &another, QObject *parent = nullptr);

    Student& operator=(const Student &another);
    ~Student();

    friend QDataStream& operator<<(QDataStream &stream, const Student &data);
    friend QDataStream& operator>>(QDataStream &stream, Student &data);

    virtual void commitToRecord() const override;
    static Student loadFromRecord(const Entity &value);

    float getScore() const;
    void setScore(float value);

    Student::State getState() const;
    
    quint8 getMinimumCredits() const;
    quint8 getMaximumCredits() const;

    virtual void addCredit(Lesson &lesson) override;
    virtual void removeCredit(Lesson &lesson) override;

signals:
    void scoreChanged(float score);

private:
    float score = 0.00;
};

QDataStream& operator<<(QDataStream &stream, const Student &data);
QDataStream& operator>>(QDataStream &stream, Student &data);

Q_DECLARE_METATYPE(Student)

#endif // STUDENT_H
