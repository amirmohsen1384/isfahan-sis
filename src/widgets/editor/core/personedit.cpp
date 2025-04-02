#include "include/widgets/editor/core/namevalidator.h"
#include "include/widgets/editor/core/personedit.h"
#include "ui_personedit.h"

PersonEdit::PersonEdit(QWidget *parent) : EntityEdit(parent)
{
    ui = new Ui::PersonEdit;
}
PersonEdit::~PersonEdit()
{
    delete ui;
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

Person PersonEdit::getInformationForPerson() const
{
    Person target = initialPerson;
    target.setIdentifier(getIdentifier());
    target.setFirstName(getFirstName());
    target.setLastName(getLastName());
    target.setUserName(getUserName());
    target.setPassword(getPassword());
    return target;
}

Person PersonEdit::getInitialPerson() const
{
    return initialPerson;
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

void PersonEdit::setInformationForPerson(const Person &value)
{
    setIdentifier(value.getIdentifier());
    setFirstName(value.getFirstName());
    setLastName(value.getLastName());
    setUserName(value.getUserName());
    setPassword(value.getPassword());
}

void PersonEdit::initialize(QWidget *target)
{
    ui->setupUi(target);
    connect(ui->firstNameEdit, &QLineEdit::textChanged, this, &PersonEdit::firstNameChanged);
    connect(ui->lastNameEdit, &QLineEdit::textChanged, this, &PersonEdit::lastNameChanged);
    connect(ui->userNameEdit, &QLineEdit::textChanged, this, &PersonEdit::userNameChanged);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &PersonEdit::passwordChanged);
    connect(this, &PersonEdit::initialPersonChanged, this, &PersonEdit::resetPerson);
    NameValidator *validator = new NameValidator(this);
    ui->firstNameEdit->setValidator(validator);
    ui->lastNameEdit->setValidator(validator);
    EntityEdit::initialize(ui->entityEdit);
}

void PersonEdit::setInitialPerson(const Person &value)
{
    this->initialPerson = value;
    emit initialPersonChanged(initialPerson);
}

void PersonEdit::resetFirstName()
{
    ui->firstNameEdit->setText(initialPerson.getFirstName());
}

void PersonEdit::resetLastName()
{
    ui->lastNameEdit->setText(initialPerson.getLastName());
}

void PersonEdit::resetUserName()
{
    ui->userNameEdit->setText(initialPerson.getUserName());
}

void PersonEdit::resetPassword()
{
    ui->passwordEdit->setText(initialPerson.getPassword());
}

void PersonEdit::resetPerson()
{
    resetIdentifier();
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
