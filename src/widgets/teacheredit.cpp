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
    connect(ui->infoEditor, &PersonEdit::firstNameChanged, this, &TeacherEdit::firstNameChanged);
    connect(ui->infoEditor, &PersonEdit::lastNameChanged, this, &TeacherEdit::lastNameChanged);
    connect(ui->infoEditor, &PersonEdit::userNameChanged, this, &TeacherEdit::userNameChanged);
    connect(ui->infoEditor, &PersonEdit::passwordChanged, this, &TeacherEdit::passwordChanged);
    connect(ui->infoEditor, &PersonEdit::identifierChanged, this, &TeacherEdit::identifierChanged);
}

TeacherEdit::~TeacherEdit()
{
    delete ui;
}

QString TeacherEdit::getFirstName() const
{
    return ui->infoEditor->getFirstName();
}

QString TeacherEdit::getLastName() const
{
    return ui->infoEditor->getLastName();
}

QString TeacherEdit::getUserName() const
{
    return ui->infoEditor->getUserName();
}

QString TeacherEdit::getPassword() const
{
    return ui->infoEditor->getLastName();
}

qint64 TeacherEdit::getIdentifier() const
{
    return ui->infoEditor->getIdentifier();
}

Teacher TeacherEdit::getInitial() const
{
    return initial;
}

Teacher TeacherEdit::getInformation() const
{
    Teacher result = initial;
    static_cast<Person>(result) = ui->infoEditor->getInformation();
    return result;
}

void TeacherEdit::setFirstName(const QString &value)
{
    ui->infoEditor->setFirstName(value);
}

void TeacherEdit::setLastName(const QString &value)
{
    ui->infoEditor->setLastName(value);
}

void TeacherEdit::setUserName(const QString &value)
{
    ui->infoEditor->setUserName(value);
}

void TeacherEdit::setPassword(const QString &value)
{
    ui->infoEditor->setPassword(value);
}

void TeacherEdit::setIdentifier(qint64 value)
{
    ui->infoEditor->setIdentifier(value);
}

void TeacherEdit::setInitial(const Teacher &value)
{
    initial = value;
    emit initialChanged(value);
}

void TeacherEdit::setInformation(const Teacher &value)
{
    ui->infoEditor->setInformation(value);
}

void TeacherEdit::resetFirstName()
{
    ui->infoEditor->resetFirstName();
}

void TeacherEdit::resetLastName()
{
    ui->infoEditor->resetLastName();
}

void TeacherEdit::resetUserName()
{
    ui->infoEditor->resetUserName();
}

void TeacherEdit::resetPassword()
{
    ui->infoEditor->resetPassword();
}

void TeacherEdit::resetIdentifier()
{
    ui->infoEditor->resetIdentifier();
}

void TeacherEdit::resetProperties()
{
    ui->infoEditor->setInitial(initial);
}
