#ifndef LESSONEDIT_H
#define LESSONEDIT_H

#include <QWidget>
#include "include/data/lesson.h"

namespace Ui {
class LessonEdit;
}

class LessonEdit : public QWidget
{
    Q_OBJECT
public:
    explicit LessonEdit(const Lesson &lesson, QWidget *parent = nullptr);
    explicit LessonEdit(QWidget *parent = nullptr);
    ~LessonEdit();

    int getCapacity() const;
    QString getName() const;
    int getCreditUnit() const;
    int getBranchNumber() const;
    qint64 getIdentifier() const;
    QDateTime getFinalExam() const;

    Lesson getInformation() const;
    Lesson getInitial() const;

public slots:
    void setName(const QString &value);
    void setCapacity(int value);
    void setCreditUnit(int value);
    void setBranchNumber(int value);
    void setIdentifier(qint64 value);
    void setFinalExam(const QDateTime &value);
    void setInformation(const Lesson &value);

    void setInitial(const Lesson &initial);

    void resetName();
    void resetCapacity();
    void resetCreditUnit();
    void resetBranchNumber();
    void resetIdentifier();
    void resetFinalExam();
    void resetProperties();

signals:
    void nameChanged(QString value);
    void capacityChanged(int value);
    void creditUnitChanged(int value);
    void branchNumberChanged(int value);
    void identifierChanged(qint64 value);
    void finalExamChanged(QDateTime value);

    void initialChanged(const Lesson &value);

private:
    Lesson initial;
    Ui::LessonEdit *ui;
};

#endif // LESSONEDIT_H
