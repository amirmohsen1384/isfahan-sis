#include "include/screens/studentpanel.h"
#include "ui_studentpanel.h"

StudentPanel::StudentPanel(QWidget *parent) : QMainWindow{parent}, ui(new Ui::StudentPanel)
{
    ui->setupUi(this);
}
