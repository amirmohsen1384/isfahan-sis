#include "personshow.h"
#include "ui_personshow.h"

PersonShow::PersonShow(QWidget *target, QWidget *parent) : EntityShow(parent)
{
    ui = new Ui::PersonShow;
    initialize(target);
}
PersonShow::PersonShow(QWidget *parent) : EntityShow(parent)
{
    ui = new Ui::PersonShow;
}
PersonShow::~PersonShow()
{
    delete ui;
}
QString PersonShow::getFirstName() const
{
    return container.getFirstName();
}

QString PersonShow::getLastName() const
{
    return container.getLastName();
}

QString PersonShow::getUserName() const
{
    return container.getUserName();
}

QString PersonShow::getPassword() const
{
    return container.getPassword();
}

void PersonShow::setFirstName(const QString &value)
{
    ui->firstNameLabel->setText(value);
    emit firstNameChanged(value);
}

void PersonShow::setLastName(const QString &value)
{
    ui->lastNameLabel->setText(value);
    emit lastNameChanged(value);
}

void PersonShow::setUserName(const QString &value)
{
    ui->userNameLabel->setText(value);
    emit userNameChanged(value);
}

void PersonShow::setPassword(const QString &value)
{
    ui->passwordLabel->setText(value);
    emit passwordChanged(value);
}

void PersonShow::initialize(QWidget *target)
{
    ui->setupUi(target);
    EntityShow::initialize(ui->entityView);
}
