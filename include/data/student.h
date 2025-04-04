#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include "lesson.h"

class Student;
using StudentList = QList<Student>;

class Student : public Person
{
    Q_OBJECT
public:
    enum class State {Rejection, Probation, Normal, Honor}; Q_ENUM(State)

public:
    Student& operator=(const Student &another);

    explicit Student(QObject *parent = nullptr);
    Student(float score, QObject *parent = nullptr);
    Student(const Student &another, QObject *parent = nullptr);

    friend QDataStream& operator<<(QDataStream &stream, const Student &data);
    friend QDataStream& operator>>(QDataStream &stream, Student &data);

    virtual void commitToRecord() const override;
    static Student loadFromRecord(const Entity &value);

    float getScore() const;

    Student::State getState() const;
    
    quint8 getMinimumCredits() const;
    quint8 getMaximumCredits() const;

    bool enrollsIn(const Lesson &target) const;

    LessonList getWaitingLessons() const;

    static QDir getRoot();
    static QFileInfoList getFiles();
    static StudentList getEntities();
    static QString getFileName(const Entity &entity);

public slots:
    void setScore(float value);

    virtual void addCredit(Lesson &target) override;
    virtual void removeCredit(Lesson &target) override;

signals:
    void scoreChanged(float score);
    void lessonQueueChanged();

private:
    float score = 0.00;
    EntityQueue queue;
};

QDataStream& operator<<(QDataStream &stream, const Student &data);
QDataStream& operator>>(QDataStream &stream, Student &data);

Q_DECLARE_METATYPE(Student)

#endif // STUDENT_H
