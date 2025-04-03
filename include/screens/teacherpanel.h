#ifndef TEACHERPANEL_H
#define TEACHERPANEL_H

#include <QMainWindow>
#include "include/data/teacher.h"
#include "include/models/enrolledmodel.h"

namespace Ui {
class TeacherPanel;
}

class TeacherPanel : public QMainWindow
{
    Q_OBJECT
public:
    explicit TeacherPanel(const Teacher &teacher, QWidget *parent = nullptr);
    explicit TeacherPanel(QWidget *parent = nullptr);
    ~TeacherPanel();

    Teacher getTeacher() const;

public slots:
    void addLesson();

    void setTeacher(const Teacher &teacher);

public slots:
    void resetTeacher();

signals:
    void teacherChanged(const Teacher &teacher);

private:
    Teacher teacher;
    EnrolledModel model;
    Ui::TeacherPanel *ui;
};

#endif // TEACHERPANEL_H
