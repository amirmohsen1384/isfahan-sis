#ifndef LESSONVIEW_H
#define LESSONVIEW_H

#include <QWidget>
#include "include/data/lesson.h"

namespace Ui {
class LessonView;
}

class LessonView : public QWidget
{
    Q_OBJECT

public:
    explicit LessonView(const Lesson &lesson, QWidget *parent = nullptr);
    explicit LessonView(QWidget *parent = nullptr);
    ~LessonView();

    Lesson getLesson() const;

public slots:
    void setLesson(const Lesson &value);
    void resetLesson();

    void copyIDNumber();

    void resetName();
    void resetIdentifier();
    void resetFinalExam();
    void resetCreditUnit();
    void resetTeacherName();
    void resetBranchNumber();
    void resetTotalCapacity();

signals:
    void lessonChanged(const Lesson &value);

private slots:

private:
    Lesson container;
    Ui::LessonView *ui;
};

#endif // LESSONVIEW_H
