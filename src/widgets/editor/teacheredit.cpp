#include "include/widgets/editor/core/namevalidator.h"
#include "include/widgets/editor/teacheredit.h"
#include "include/errors/education.h"
#include "ui_teacheredit.h"

TeacherEdit::TeacherEdit(const Teacher &info, QWidget *parent) : TeacherEdit(parent)
{
    setDefault(info);
}

TeacherEdit::TeacherEdit(QWidget *parent) : QWidget(parent), ui(new Ui::TeacherEdit)
{
    ui->setupUi(this);
    togglePasswordShow(true);
    connect(this, &TeacherEdit::defaultChanged, this, &TeacherEdit::resetTeacher);

    NameValidator *validator = new NameValidator(this);
    ui->firstNameEdit->setValidator(validator);
    ui->lastNameEdit->setValidator(validator);

    QIntValidator *idValidator = new QIntValidator;
    ui->idEdit->setValidator(idValidator);
    idValidator->setBottom(1);
}

TeacherEdit::~TeacherEdit()
{
    delete ui;
}

QString TeacherEdit::getFirstName() const
{
    return ui->firstNameEdit->text();
}

QString TeacherEdit::getLastName() const
{
    return ui->lastNameEdit->text();
}

QString TeacherEdit::getUserName() const
{
    return ui->userNameEdit->text();
}

QString TeacherEdit::getPassword() const
{
    return ui->passwordEdit->text();
}

qint64 TeacherEdit::getIdentifier() const
{
    return ui->idEdit->text().toLongLong();
}

Teacher TeacherEdit::getContainer() const
{
    Teacher result = container;
    result.setFirstName(this->getFirstName());
    result.setLastName(this->getLastName());
    result.setUserName(this->getUserName());
    result.setPassword(this->getPassword());
    result.setIdentifier(this->getIdentifier());
    return result;
}

Teacher TeacherEdit::getDefault() const
{
    return container;
}

void TeacherEdit::setFirstName(const QString &value)
{
    ui->firstNameEdit->setText(value);
}

void TeacherEdit::setLastName(const QString &value)
{
    ui->lastNameEdit->setText(value);
}

void TeacherEdit::setUserName(const QString &value)
{
    ui->userNameEdit->setText(value);
}

void TeacherEdit::setPassword(const QString &value)
{
    ui->passwordEdit->setText(value);
}

void TeacherEdit::setIdentifier(qint64 value)
{
    ui->idEdit->setText(QString::number(value < 1 ? 1 : value));
}

void TeacherEdit::setContainer(const Teacher &value)
{
    setFirstName(value.getFirstName());
    setLastName(value.getLastName());
    setUserName(value.getUserName());
    setPassword(value.getPassword());
    setIdentifier(value.getIdentifier());
}

void TeacherEdit::setDefault(const Teacher &value)
{
    container = value;
    emit defaultChanged(value);
}

void TeacherEdit::resetFirstName()
{
    setFirstName(container.getFirstName());
}

void TeacherEdit::resetLastName()
{
    setLastName(container.getLastName());
}

void TeacherEdit::resetUserName()
{
    setUserName(container.getUserName());
}

void TeacherEdit::resetPassword()
{
    setPassword(container.getPassword());
}

void TeacherEdit::resetIdentifier()
{
    qint64 value = container.getIdentifier();
    setIdentifier(container.isNull() ? 1 : value);
}

void TeacherEdit::resetTeacher()
{
    resetFirstName();
    resetLastName();
    resetUserName();
    resetPassword();
    resetIdentifier();
    if(!container.isNull()) {
        setWindowTitle(QString("%1 - Teacher Editor").arg(container.getFullName()));
    }
}

void TeacherEdit::togglePasswordShow(bool value)
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

void TeacherEdit::validateEditor() const
{
    qint64 value = this->getIdentifier();
    if(value == 0) {
        throw InvalidIdentifierException();
    }

    if(ui->idEdit->text().isEmpty()) {
        throw EmptyIdentifierException();
    }

    if(QFile::exists(Teacher::getFileName(Entity(value)))) {
        throw InvalidIdentifierException();
    }

    if(ui->firstNameEdit->text().isEmpty()) {
        throw EmptyFirstNameException();
    }

    if(ui->lastNameEdit->text().isEmpty()) {
        throw EmptyLastNameException();
    }

    if(ui->userNameEdit->text().isEmpty()) {
        throw EmptyUserNameException();
    }

    if(this->getPassword().isEmpty()) {
        throw EmptyPasswordException();
    }

    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[\\W_])[A-Za-z\\d\\W_]{8,}$");
    if(!regex.match(this->getPassword()).hasMatch()) {
        throw InvalidPasswordException();
    }
}
