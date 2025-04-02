#ifndef LESSONEDIT_H
#define LESSONEDIT_H

#include <QWidget>
#include "core/entityedit.h"
#include "include/data/lesson.h"

namespace Ui {
class LessonEdit;
}

class LessonEdit : public EntityEdit
{
    Q_OBJECT
public:
    explicit LessonEdit(const Lesson &lesson, QWidget *parent = nullptr);
    explicit LessonEdit(QWidget *parent = nullptr);
    ~LessonEdit();

    QString getName() const;
    int getCreditUnit() const;
    int getBranchNumber() const;
    int getTotalCapacity() const;
    QDateTime getFinalExam() const;

    Lesson getInitial() const;
    Lesson getInformation() const;

public slots:
    void setFinalExam(const QDateTime &value);
    void setName(const QString &value);
    void setTotalCapacity(int value);
    void setBranchNumber(int value);
    void setCreditUnit(int value);

    void setInformation(const Lesson &value);
    void setInitial(const Lesson &initial);

    void resetName();
    void resetFinalExam();
    void resetCreditUnit();
    void resetBranchNumber();
    void resetTotalCapacity();

    void resetLesson();

signals:
    void nameChanged(QString value);
    void creditUnitChanged(int value);
    void branchNumberChanged(int value);
    void totalCapacityChanged(int value);
    void finalExamChanged(QDateTime value);
    void initialChanged(const Lesson &value);

private:
    Lesson initial;
    Ui::LessonEdit *ui;
};

#endif // LESSONEDIT_H
