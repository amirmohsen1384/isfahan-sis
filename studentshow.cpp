#include "studentshow.h"
#include "ui_studentshow.h"

StudentShow::StudentShow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentShow)
{
    ui->setupUi(this);
}

StudentShow::~StudentShow()
{
    delete ui;
}
