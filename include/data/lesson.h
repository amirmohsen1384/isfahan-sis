#ifndef LESSON_H
#define LESSON_H

#include <QDate>
#include "entity.h"

class Lesson;
class Teacher;
class Student;

using LessonList = QList<Lesson>;

class Lesson : public Entity
{
    Q_OBJECT
public:
    explicit Lesson(QObject *parent = nullptr);
    Lesson(const Lesson &other, QObject *parent = nullptr);

    Lesson& operator=(const Lesson &other);

    bool hasTeacher() const;

    Teacher getTeacher() const;

    bool isAbleToEnroll() const;

    quint8 getCreditUnit() const;

    QDateTime getFinalExam() const;

    quint64 getBranchNumber() const;

    quint64 getLeftCapacity() const;

    quint8 getTotalCapacity() const;

    QList<Student> getEnrolledStudents() const;

    QString getName() const;

public slots:
    void setName(const QString &value);

    void setCreditUnit(quint8 value);

    void setBranchNumber(quint64 value);

    void setTotalCapacity(quint8 value);

    void setFinalExam(const QDateTime &value);

    virtual void commitToRecord() const override;

    virtual void setIdentifier(const qint64 &value) override;

    friend QDataStream& operator<<(QDataStream &stream, const Lesson &data);
    friend QDataStream& operator>>(QDataStream &stream, Lesson &data);
    static Lesson loadFromRecord(const Entity &value);


    static QString getLessonFileName(const Entity &value);
    static LessonList getExistingLessons();
    static QFileInfoList getLessonFiles();
    static QDir getLessonsDirectory();

private slots:
    void setTeacher(const Teacher &value);

    void addStudent(const Student &value);

    void removeStudent(const Student &value);

    friend class Student;
    friend class Teacher;

signals:
    void enrolledStudentsChanged();
    void nameChanged(QString value);
    void teacherChanged(Entity value);
    void creditUnitChanged(quint8 value);
    void branchNumberChanged(quint8 value);
    void finalExamChanged(QDateTime value);
    void totalCapacityChanged(quint64 value);

private:
    EntityList enrolledStudents;
    quint64 branchNumber = 0;
    quint8 totalCapacity;
    QDateTime finalExam;
    quint8 creditUnit;
    Entity teacher;
    QString name;
};

QDataStream& operator<<(QDataStream &stream, const Lesson &data);
QDataStream& operator>>(QDataStream &stream, Lesson &data);

Q_DECLARE_METATYPE(Lesson)

#endif // LESSON_H
