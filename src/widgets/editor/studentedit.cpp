#include "include/widgets/studentedit.h"
#include "ui_studentedit.h"

StudentEdit::StudentEdit(const Student &initial, QWidget *parent) : StudentEdit(parent)
{
    setInitial(initial);
}

StudentEdit::StudentEdit(QWidget *parent) : QWidget(parent), ui(new Ui::StudentEdit)
{
    ui->setupUi(this);
    connect(this, &StudentEdit::initialChanged, this, &StudentEdit::resetProperties);
    connect(ui->scoreEdit, &QDoubleSpinBox::valueChanged, this, &StudentEdit::scoreChanged);
    connect(ui->infoEditor, &PersonEdit::lastNameChanged, this, &StudentEdit::lastNameChanged);
    connect(ui->infoEditor, &PersonEdit::userNameChanged, this, &StudentEdit::userNameChanged);
    connect(ui->infoEditor, &PersonEdit::passwordChanged, this, &StudentEdit::passwordChanged);
    connect(ui->infoEditor, &PersonEdit::firstNameChanged, this, &StudentEdit::firstNameChanged);
    connect(ui->infoEditor, &PersonEdit::identifierChanged, this, &StudentEdit::identifierChanged);
}

StudentEdit::~StudentEdit()
{
    delete ui;
}

QString StudentEdit::getFirstName() const
{
    return ui->infoEditor->getFirstName();
}

QString StudentEdit::getLastName() const
{
    return ui->infoEditor->getLastName();
}

QString StudentEdit::getUserName() const
{
    return ui->infoEditor->getUserName();
}

QString StudentEdit::getPassword() const
{
    return ui->infoEditor->getPassword();
}

qint64 StudentEdit::getIdentifier() const
{
    return ui->infoEditor->getIdentifier();
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
    static_cast<Person>(target) = ui->infoEditor->getInformation();
    target.setScore(this->getScore());
    return target;
}

void StudentEdit::setFirstName(const QString &value)
{
    ui->infoEditor->setFirstName(value);
}

void StudentEdit::setLastName(const QString &value)
{
    ui->infoEditor->setLastName(value);
}

void StudentEdit::setUserName(const QString &value)
{
    ui->infoEditor->setUserName(value);
}

void StudentEdit::setPassword(const QString &value)
{
    ui->infoEditor->setPassword(value);
}

void StudentEdit::setIdentifier(qint64 value)
{
    ui->infoEditor->setIdentifier(value);
}

void StudentEdit::resetScore()
{
    setScore(initial.getScore());
}

void StudentEdit::resetProperties()
{
    ui->infoEditor->setInitial(initial);
    resetScore();
}

void StudentEdit::setScore(float score)
{
    ui->scoreEdit->setValue(score);
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

void StudentEdit::resetFirstName()
{
    ui->infoEditor->resetFirstName();
}

void StudentEdit::resetLastName()
{
    ui->infoEditor->resetLastName();
}

void StudentEdit::resetUserName()
{
    ui->infoEditor->resetUserName();
}

void StudentEdit::resetPassword()
{
    ui->infoEditor->resetPassword();
}

void StudentEdit::resetIdentifier()
{
    ui->infoEditor->resetIdentifier();
}
