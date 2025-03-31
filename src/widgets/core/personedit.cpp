#include "include/widgets/core/namevalidator.h"
#include "include/widgets/core/personedit.h"
#include "ui_personedit.h"

PersonEdit::PersonEdit(const Person &initial, QWidget *parent) : PersonEdit(parent)
{
    setInitial(initial);
}

PersonEdit::PersonEdit(QWidget *parent) : QWidget(parent), ui(new Ui::PersonEdit)
{
    ui->setupUi(this);
    connect(ui->entityEdit, &EntityEdit::identifierAccepted, this, &PersonEdit::identifierChanged);
    connect(ui->firstNameEdit, &QLineEdit::textChanged, this, &PersonEdit::firstNameChanged);
    connect(ui->lastNameEdit, &QLineEdit::textChanged, this, &PersonEdit::lastNameChanged);
    connect(ui->userNameEdit, &QLineEdit::textChanged, this, &PersonEdit::userNameChanged);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &PersonEdit::passwordChanged);
    connect(this, &PersonEdit::initialChanged, this, &PersonEdit::resetProperties);

    NameValidator *validator = new NameValidator(this);
    ui->firstNameEdit->setValidator(validator);
    ui->lastNameEdit->setValidator(validator);
}

PersonEdit::~PersonEdit()
{
    delete ui;
}

Person PersonEdit::getInformation() const
{
    Person target = initial;
    target.setFirstName(ui->firstNameEdit->text());
    target.setLastName(ui->lastNameEdit->text());
    target.setUserName(ui->userNameEdit->text());
    target.setPassword(ui->passwordEdit->text());
    target.setIdentifier(ui->entityEdit->getIdentifier());
    return target;
}

QString PersonEdit::getFirstName() const
{
    return ui->firstNameEdit->text();
}

QString PersonEdit::getLastName() const
{
    return ui->lastNameEdit->text();
}

QString PersonEdit::getUserName() const
{
    return ui->userNameEdit->text();
}

QString PersonEdit::getPassword() const
{
    return ui->passwordEdit->text();
}

qint64 PersonEdit::getIdentifier() const
{
    return ui->entityEdit->getIdentifier();
}

Person PersonEdit::getInitial() const
{
    return initial;
}

void PersonEdit::setFirstName(const QString &value)
{
    ui->firstNameEdit->setText(value);
}

void PersonEdit::setLastName(const QString &value)
{
    ui->lastNameEdit->setText(value);
}

void PersonEdit::setUserName(const QString &value)
{
    ui->userNameEdit->setText(value);
}

void PersonEdit::setPassword(const QString &value)
{
    ui->passwordEdit->setText(value);
}

void PersonEdit::setIdentifier(const qint64 &value)
{
    ui->entityEdit->setIdentifier(value);
}

void PersonEdit::setInformation(const Person &value)
{
    setFirstName(value.getFirstName());
    setLastName(value.getLastName());
    setUserName(value.getUserName());
    setPassword(value.getPassword());
    setIdentifier(value.getIdentifier());
}

void PersonEdit::setInitial(const Person &value)
{
    this->initial = value;
    emit initialChanged(initial);
}

void PersonEdit::resetIdentifier()
{
    ui->entityEdit->resetIdentifier();
}

void PersonEdit::resetFirstName()
{
    ui->firstNameEdit->setText(initial.getFirstName());
}

void PersonEdit::resetLastName()
{
    ui->lastNameEdit->setText(initial.getLastName());
}

void PersonEdit::resetUserName()
{
    ui->userNameEdit->setText(initial.getUserName());
}

void PersonEdit::resetPassword()
{
    ui->passwordEdit->setText(initial.getPassword());
}

void PersonEdit::resetProperties()
{
    ui->entityEdit->resetIdentifier();
    resetFirstName();
    resetLastName();
    resetUserName();
    resetPassword();
}

void PersonEdit::toggleShowPassword(bool state)
{
    if(state) {
        ui->showPasswordButton->setIcon(QIcon(":/root/dialogs/password-show.png"));
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
    } else {
        ui->showPasswordButton->setIcon(QIcon(":/root/dialogs/password-hide.png"));
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
    }
}
