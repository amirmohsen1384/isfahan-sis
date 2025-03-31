#include "include/widgets/teacheredit.h"
#include "ui_teacheredit.h"

TeacherEdit::TeacherEdit(const Teacher &initial, QWidget *parent) : TeacherEdit(parent)
{
    setInitial(initial);
}

TeacherEdit::TeacherEdit(QWidget *parent) : QWidget(parent), ui(new Ui::TeacherEdit)
{
    ui->setupUi(this);
    connect(this, &TeacherEdit::initialChanged, this, &TeacherEdit::resetProperties);
}

TeacherEdit::~TeacherEdit()
{
    delete ui;
}

Teacher TeacherEdit::getInitial() const
{
    return initial;
}

void TeacherEdit::setInitial(const Teacher &value)
{
    initial = value;
    emit initialChanged(value);
}

void TeacherEdit::resetProperties()
{
    ui->infoEditor->setInformation(initial);
}


