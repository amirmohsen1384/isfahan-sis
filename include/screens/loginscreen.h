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
    explicit LoginScreen(QWidget *parent = nullptr);
    ~LoginScreen();

public slots:
    bool authorize();
    void openAccountDialog();
    void togglePasswordShow(bool value);

private:
    Ui::LoginScreen *ui;
};

#endif // LOGINSCREEN_H
