#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QMainWindow>
#include "include/data/student.h"
#include "include/data/teacher.h"

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QMainWindow
{
    Q_OBJECT
public:
    enum class AuthorizedUser {None, Student, Teacher};

    explicit LoginScreen(QWidget *parent = nullptr);
    ~LoginScreen();

    LoginScreen::AuthorizedUser getResult() const;
    Teacher getAuthorizedTeacher() const;
    Student getAuthorizedStudent() const;

public slots:
    bool authorize();
    void openAccountDialog();
    void togglePasswordShow(bool value);

private:
    AuthorizedUser result = AuthorizedUser::None;
    Teacher authorizedTeacher;
    Student authorizedStudent;
    Ui::LoginScreen *ui;
};

#endif // LOGINSCREEN_H
