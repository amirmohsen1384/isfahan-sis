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
    explicit TeacherPanel(const Teacher &target, QWidget *parent = nullptr);
    explicit TeacherPanel(QWidget *parent = nullptr);

    Teacher getTeacher() const;
    ~TeacherPanel();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

public slots:
    void goUp();
    void goDown(const QModelIndex &index);

public slots:
    void addLesson();
    void viewEntity();
    void removeEntity();

public slots:
    void viewProfile();
    void editProfile();

public slots:
    void resetTeacher();
    void setTeacher(const Teacher &teacher);

private slots:
    void toggleControlButtons();
    void toggleControlButtons(const QModelIndex &index);

signals:
    void teacherChanged(const Teacher &teacher);

private:
    EnrolledModel model;
    Ui::TeacherPanel *ui;
    Teacher &teacher = model.target;
};

#endif // TEACHERPANEL_H
