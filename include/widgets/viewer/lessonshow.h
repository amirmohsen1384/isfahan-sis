#ifndef LESSONSHOW_H
#define LESSONSHOW_H

#include "core/entityshow.h"
#include "include/data/lesson.h"

namespace Ui {
class LessonShow;
}

class LessonShow : public EntityShow
{
    Q_OBJECT
public:
    explicit LessonShow(QWidget *parent = nullptr);
    ~LessonShow();

    QString getName() const;

    Entity getTeacher() const;

    quint64 getBranchNumber() const;

    QDateTime getFinalExam() const;

    quint8 getTotalCapacity() const;

    quint8 getCreditUnit() const;

    Lesson getLesson() const;

public slots:
    void setName(const QString &value);

    void setBranchNumber(quint64 value);

    void setFinalExam(const QDateTime &time);

    void setCreditUnit(quint8 value);

    void setLesson(const Lesson &data);

signals:
    void lessonChanged(const Lesson &container);

    void nameChanged(const QString &value);

    void teacherNameChanged(const Entity &value);

    void branchNumberChanged(quint64 value);

    void finalExamChanged(const QDateTime &value);

    void creditUnitChanged(quint8 value);

protected:
    void resetName();

    void resetLesson();

    void resetCapacity();

    void resetFinalExam();

    void resetCreditUnit();

    void resetTeacherName();

    void resetBranchNumber();

    virtual void initialize(QWidget *target) override;

private:
    Lesson initial;
    Ui::LessonShow *ui;
};

#endif // LESSONSHOW_H
