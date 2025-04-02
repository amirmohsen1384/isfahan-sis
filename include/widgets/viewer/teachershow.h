#ifndef TEACHERSHOW_H
#define TEACHERSHOW_H

#include <QWidget>

namespace Ui {
class TeacherShow;
}

class TeacherShow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherShow(QWidget *parent = nullptr);
    ~TeacherShow();

private:
    Ui::TeacherShow *ui;
};

#endif // TEACHERSHOW_H
