#include "teachershow.h"
#include "ui_teachershow.h"

TeacherShow::TeacherShow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeacherShow)
{
    ui->setupUi(this);
}

TeacherShow::~TeacherShow()
{
    delete ui;
}
