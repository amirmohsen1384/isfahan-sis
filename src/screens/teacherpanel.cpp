#include "teacherpanel.h"
#include "ui_teacherpanel.h"

TeacherPanel::TeacherPanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TeacherPanel)
{
    ui->setupUi(this);
}

TeacherPanel::~TeacherPanel()
{
    delete ui;
}
