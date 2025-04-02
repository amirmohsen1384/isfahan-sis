#include "include/widgets/editor/core/namevalidator.h"
#include "include/widgets/editor/studentedit.h"
#include "ui_studentedit.h"

StudentEdit::StudentEdit(const Student &info, QWidget *parent) : StudentEdit(parent)
{
    setDefault(info);
}

StudentEdit::StudentEdit(QWidget *parent) : QWidget(parent), ui(new Ui::StudentEdit)
{
    ui->setupUi(this);
    togglePasswordShow(true);
    connect(this, &StudentEdit::defaultChanged, this, &StudentEdit::resetStudent);

    NameValidator *validator = new NameValidator(this);
    ui->firstNameEdit->setValidator(validator);
    ui->lastNameEdit->setValidator(validator);

    QIntValidator *idValidator = new QIntValidator;
    ui->idEdit->setValidator(idValidator);
    idValidator->setBottom(1);
}

StudentEdit::~StudentEdit()
{
    delete ui;
}

QString StudentEdit::getFirstName() const
{
    return ui->firstNameEdit->text();
}

QString StudentEdit::getLastName() const
{
    return ui->lastNameEdit->text();
}

QString StudentEdit::getUserName() const
{
    return ui->userNameEdit->text();
}

QString StudentEdit::getPassword() const
{
    return ui->passwordEdit->text();
}

qint64 StudentEdit::getIdentifier() const
{
    return ui->idEdit->text().toLongLong();
}

float StudentEdit::getScore() const
{
    return ui->scoreEdit->value();
}

Student StudentEdit::getContainer() const
{
    Student result = container;
    result.setIdentifier(this->getIdentifier());
    result.setFirstName(this->getFirstName());
    result.setLastName(this->getLastName());
    result.setUserName(this->getUserName());
    result.setPassword(this->getPassword());
    result.setScore(this->getScore());
    return result;
}

Student StudentEdit::getDefault() const
{
    return container;
}

void StudentEdit::setFirstName(const QString &value)
{
    ui->firstNameEdit->setText(value);
}

void StudentEdit::setLastName(const QString &value)
{
    ui->lastNameEdit->setText(value);
}

void StudentEdit::setUserName(const QString &value)
{
    ui->userNameEdit->setText(value);
}

void StudentEdit::setPassword(const QString &value)
{
    ui->passwordEdit->setText(value);
}

void StudentEdit::setIdentifier(qint64 value)
{
    ui->idEdit->setText(QString::number(value < 1 ? 1 : value));
}

void StudentEdit::setScore(float value)
{
    ui->scoreEdit->setValue(value);
}

void StudentEdit::setContainer(const Student &value)
{
    setFirstName(value.getFirstName());
    setLastName(value.getLastName());
    setUserName(value.getUserName());
    setPassword(value.getPassword());
    setIdentifier(value.getIdentifier());
    setScore(value.getScore());
}

void StudentEdit::setDefault(const Student &value)
{
    container = value;
    emit defaultChanged(value);
}

void StudentEdit::resetFirstName()
{
    setFirstName(container.getFirstName());
}

void StudentEdit::resetLastName()
{
    setLastName(container.getLastName());
}

void StudentEdit::resetUserName()
{
    setUserName(container.getUserName());
}

void StudentEdit::resetPassword()
{
    setPassword(container.getPassword());
}

void StudentEdit::resetIdentifier()
{
    qint64 value = container.getIdentifier();
    setIdentifier(container.isNull() ? 1 : value);
}

void StudentEdit::resetScore()
{
    setScore(container.getScore());
}

void StudentEdit::resetStudent()
{
    resetIdentifier();
    resetFirstName();
    resetLastName();
    resetUserName();
    resetPassword();
    resetScore();
    if(!container.isNull()) {
        setWindowTitle(QString("%1 - Student Editor").arg(container.getFullName()));
    }
}

void StudentEdit::togglePasswordShow(bool value)
{
    if(value)
    {
        ui->showPasswordButton->setIcon(QIcon(":/root/dialogs/password-hide.png"));
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        ui->showPasswordButton->setToolTip("Show Password");
    }
    else
    {
        ui->showPasswordButton->setIcon(QIcon(":/root/dialogs/password-show.png"));
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        ui->showPasswordButton->setToolTip("Hide Password");
    }
}
