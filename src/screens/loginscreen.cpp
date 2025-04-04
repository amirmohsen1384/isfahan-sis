#include "include/dialogs/accountdialog.h"
#include "include/screens/teacherpanel.h"
#include "include/screens/loginscreen.h"
#include "include/screens/studentpanel.h"
#include "ui_loginscreen.h"
#include <QMessageBox>

LoginScreen::LoginScreen(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

bool LoginScreen::authorize()
{
    const QString username = ui->userNameEdit->text();
    const QString password = ui->passwordEdit->text();

    QMessageBox message(this);
    message.setIcon(QMessageBox::Critical);
    message.setWindowTitle("Authorization Error!");

    if(username.isEmpty() || password.isEmpty()) {
        message.setText("The username or password is empty!");
        message.exec();
        return false;
    }

    TeacherList teachers = Teacher::getEntities();
    for(const Teacher &target : teachers) {
        if(target.getUserName() == username && target.getPassword() == password) {
            TeacherPanel *panel = new TeacherPanel(target, this);
            panel->show();
            this->hide();
            return true;
        }
    }

    StudentList students = Student::getEntities();
    for(const Student &target : students) {
        if(target.getUserName() == username && target.getPassword() == password) {
            StudentPanel *panel = new StudentPanel(target, this);
            panel->show();
            this->hide();
            return true;
        }
    }

    message.setText("There's no user with this username or password.");
    message.exec();
    return false;
}

void LoginScreen::openAccountDialog()
{
    AccountDialog dialog(this);
    dialog.setModal(true);
    dialog.exec();
}

void LoginScreen::togglePasswordShow(bool value)
{
    if(value)
    {
        ui->showPasswordButton->setIcon(QIcon(":/root/dialogs/password-hide.png"));
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        ui->showPasswordButton->setToolTip("Show Password");
    }
    else
    {
        ui->showPasswordButton->setIcon(QIcon(":/root/dialogs/password-show.png"));
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        ui->showPasswordButton->setToolTip("Hide Password");
    }
}
