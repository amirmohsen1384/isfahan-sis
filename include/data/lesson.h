#ifndef LESSON_H
#define LESSON_H

#include <QDate>
#include "entity.h"
#include "include/data/student.h"
#include "include/data/teacher.h"
#include "include/data/core/queue.h"

class Lesson;
using LessonList = QList<Lesson>;

class Lesson : public Entity
{
    Q_OBJECT
public:
    Lesson& operator=(const Lesson &other);

    explicit Lesson(QObject *parent = nullptr);
    Lesson(const Lesson &other, QObject *parent = nullptr);

    QString getName() const;

    bool hasTeacher() const;

    Teacher getTeacher() const;

    bool isAbleToEnroll() const;

    quint8 getCreditUnit() const;

    QDateTime getFinalExam() const;

    quint64 getBranchNumber() const;

    quint64 getLeftCapacity() const;

    quint8 getTotalCapacity() const;

    StudentList getEnrolledStudents() const;

public slots:
    void setName(const QString &value);

    void setCreditUnit(quint8 value);

    void setBranchNumber(quint64 value);

    void setTotalCapacity(quint8 value);

    void setFinalExam(const QDateTime &value);

    virtual void commitToRecord() const override;

public:
    friend QDataStream& operator<<(QDataStream &stream, const Lesson &data);
    friend QDataStream& operator>>(QDataStream &stream, Lesson &data);
    static Lesson loadFromRecord(const Entity &value);


    static QString getFileName(const Entity &value);
    static LessonList getEntities();
    static QFileInfoList getFiles();
    static QDir getDirectory();

private:
    CircularQueue<Entity> waitingList;
    friend class Student;
    friend class Teacher;

signals:
    void nameChanged(QString value);
    void creditUnitChanged(quint8 value);
    void branchNumberChanged(quint8 value);
    void finalExamChanged(QDateTime value);
    void totalCapacityChanged(quint64 value);

private:
    quint64 branchNumber = 0;
    quint8 totalCapacity;
    QDateTime finalExam;
    quint8 creditUnit;
    QString name;
};

QDataStream& operator<<(QDataStream &stream, const Lesson &data);
QDataStream& operator>>(QDataStream &stream, Lesson &data);

Q_DECLARE_METATYPE(Lesson)

#endif // LESSON_H
