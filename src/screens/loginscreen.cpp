#include "include/dialogs/accountdialog.h"
#include "include/screens/loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::openAccountDialog()
{
    AccountDialog dialog(this);
    dialog.setModal(true);
    dialog.exec();
}
