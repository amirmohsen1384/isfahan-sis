#ifndef LESSONDIALOG_H
#define LESSONDIALOG_H

#include <QDialog>
#include "include/data/lesson.h"

namespace Ui { class LessonDialog; }

class LessonDialog : public QDialog
{
    Q_OBJECT
public:
    LessonDialog(const Lesson &container, QWidget *parent = nullptr);
    LessonDialog(QWidget *parent = nullptr);

    Lesson getLesson() const;

public slots:
    void setLesson(const Lesson &lesson);

public slots:
    void resetLesson();
    virtual void accept() override;

signals:
    void lessonChanged(const Lesson &lesson);

private:
    Ui::LessonDialog *ui;
};

#endif // LESSONDIALOG_H
