#ifndef LESSON_H
#define LESSON_H

#include <QDate>
#include <QQueue>
#include "entity.h"
#include "include/data/core/queue.h"

class Lesson;
class Student;
class Teacher;
using LessonList = QList<Lesson>;
using EntityQueue = QQueue<Entity>;

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

    QList<Student> getWaitingStudents() const;

    QList<Student> getEnrolledStudents() const;

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

    static int getTotalCredit(const LessonList &container);
    static int getTotalCredit(const EntityList &container);

    static QString getFileName(const Entity &value);
    static LessonList getEntities();
    static QFileInfoList getFiles();
    static QDir getRoot();

    friend class Student;
    friend class Teacher;

signals:
    void nameChanged(QString value);
    void creditUnitChanged(quint8 value);
    void branchNumberChanged(quint8 value);
    void finalExamChanged(QDateTime value);
    void totalCapacityChanged(quint64 value);

private:
    QDateTime finalExam = QDateTime::currentDateTime();
    quint64 branchNumber = 0;
    quint8 totalCapacity = 0;
    EntityQueue waitingList;
    quint8 creditUnit = 0;
    QString name;
};

QDataStream& operator<<(QDataStream &stream, const Lesson &data);
QDataStream& operator>>(QDataStream &stream, Lesson &data);

Q_DECLARE_METATYPE(Lesson)

#endif // LESSON_H
