#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include "lesson.h"

class Teacher;
using TeacherList = QList<Teacher>;

class Teacher : public Person
{
    Q_OBJECT
public:
    Teacher& operator=(const Teacher &another);

    explicit Teacher(QObject *parent = nullptr);
    Teacher(const Teacher &another, QObject *parent = nullptr);

    virtual void commitToRecord() const override;
    static Teacher loadFromRecord(const Entity &value);

    bool teaches(const Lesson &target) const;

    virtual void addCredit(Lesson &target) override;
    virtual void removeCredit(Lesson &target) override;

    friend QDataStream& operator<<(QDataStream &stream, const Teacher &data);
    friend QDataStream& operator>>(QDataStream &stream, Teacher &data);

    static QDir getRoot();
    static QFileInfoList getFiles();
    static TeacherList getEntities();
    static QString getFileName(const Entity &entity);
};

QDataStream& operator<<(QDataStream &stream, const Teacher &data);
QDataStream& operator>>(QDataStream &stream, Teacher &data);

Q_DECLARE_METATYPE(Teacher)

#endif // TEACHER_H
