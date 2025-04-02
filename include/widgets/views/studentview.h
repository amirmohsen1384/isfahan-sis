#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

#include <QWidget>
#include "include/data/student.h"

namespace Ui {
class StudentView;
}

class StudentView : public QWidget
{
    Q_OBJECT

public:
    explicit StudentView(const Student &container, QWidget *parent = nullptr);
    explicit StudentView(QWidget *parent = nullptr);
    ~StudentView();

    Student getStudent() const;
    bool isPasswordVisible() const;

public slots:
    void setStudent(const Student &value);
    void setPasswordVisible(bool value);
    void copyIDNumber();
    void resetStudent();

    void resetCreditCount();
    void resetIdentifier();
    void resetUserName();
    void resetPassword();
    void resetScore();
    void resetName();

signals:
    void studentChanged(const Student &value);

private:
    Student container;
    Ui::StudentView *ui;
};

#endif // STUDENTVIEW_H
