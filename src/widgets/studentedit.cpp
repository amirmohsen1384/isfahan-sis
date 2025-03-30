#include "studentedit.h"
#include "ui_studentedit.h"

StudentEdit::StudentEdit(const Student &initial, QWidget *parent) : StudentEdit(parent)
{
    setInitial(initial);
}

StudentEdit::StudentEdit(QWidget *parent) : QWidget(parent), ui(new Ui::StudentEdit)
{
    ui->setupUi(this);
    connect(this, &StudentEdit::initialChanged, this, &StudentEdit::resetProperties);
}

StudentEdit::~StudentEdit()
{
    delete ui;
}

float StudentEdit::getScore() const
{
    return ui->scoreEdit->value();
}

Student StudentEdit::getInitial() const
{
    return initial;
}

Student StudentEdit::getInformation() const
{
    Student target = initial;
    target.setScore(getScore());
    static_cast<Person>(target) = ui->infoEditor->getInformation();
    return target;
}

void StudentEdit::resetScore()
{
    setScore(initial.getScore());
}

void StudentEdit::resetProperties()
{
    ui->infoEditor->resetProperties();
    this->resetScore();
}

void StudentEdit::setInitial(const Student &info)
{
    initial = info;
    emit initialChanged(initial);
}

void StudentEdit::setInformation(const Student &info)
{
    ui->infoEditor->setInformation(info);
    setScore(info.getScore());
}
