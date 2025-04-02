#ifndef TEACHERVIEW_H
#define TEACHERVIEW_H

#include <QWidget>
#include "include/data/teacher.h"

namespace Ui { class TeacherView; }

class TeacherView : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherView(const Teacher &container, QWidget *parent = nullptr);
    explicit TeacherView(QWidget *parent = nullptr);
    ~TeacherView();

    Teacher getTeacher() const;
    bool isPasswordVisible() const;

public slots:
    void setTeacher(const Teacher &value);
    void setPasswordVisible(bool value);
    void copyIDNumber();
    void resetTeacher();

    void resetCreditCount();
    void resetIdentifier();
    void resetUserName();
    void resetPassword();
    void resetName();

signals:
    void teacherChanged(const Teacher &value);

private:
    Teacher container;
    Ui::TeacherView *ui;
};

#endif // TEACHERVIEW_H
