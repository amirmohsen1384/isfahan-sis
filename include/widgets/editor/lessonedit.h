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
    explicit LessonEdit(const Lesson &container, QWidget *parent = nullptr);
    explicit LessonEdit(QWidget *parent = nullptr);
    ~LessonEdit();

    QString getName() const;
    qint64 getIdentifier() const;
    int getTotalCapacity() const;
    QDateTime getFinalExam() const;
    int getBranchNumber() const;
    int getCreditUnit() const;
    Lesson getDefault() const;
    Lesson getData() const;

    void validateEditor() const;

public slots:
    void setName(const QString &value);
    void setTotalCapacity(int value);
    void setFinalExam(const QDateTime &data);
    void setIdentifier(qint64 value);
    void setBranchNumber(int value);
    void setCreditUnit(int value);
    void setDefault(const Lesson &value);
    void setData(const Lesson &value);

public slots:
    void resetName();
    void resetTotalCapacity();
    void resetFinalExam();
    void resetIdentifier();
    void resetBranchNumber();
    void resetCreditUnit();
    void resetLesson();

signals:
    void defaultChanged(const Lesson &value);

private:
    Lesson container;
    Ui::LessonEdit *ui;
};

#endif // LESSONEDIT_H
