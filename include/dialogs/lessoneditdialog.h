#ifndef LESSONEDITDIALOG_H
#define LESSONEDITDIALOG_H

#include <QDialog>
#include "include/data/lesson.h"

namespace Ui { class LessonEditDialog; }

class LessonEditDialog : public QDialog
{
    Q_OBJECT
public:
    LessonEditDialog(const Lesson &container, QWidget *parent = nullptr);
    LessonEditDialog(QWidget *parent = nullptr);

    Lesson getLesson() const;

public slots:
    void setLesson(const Lesson &lesson);

public slots:
    void resetLesson();
    virtual void accept() override;

signals:
    void lessonChanged(const Lesson &lesson);

private:
    Ui::LessonEditDialog *ui;
};

#endif // LESSONEDITDIALOG_H
