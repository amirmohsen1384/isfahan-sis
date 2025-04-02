#include "include/widgets/views/teacherview.h"
#include "ui_teacherview.h"
#include <QClipboard>

TeacherView::TeacherView(const Teacher &container, QWidget *parent) : TeacherView(parent)
{
    setTeacher(container);
}

TeacherView::TeacherView(QWidget *parent) : QWidget(parent), ui(new Ui::TeacherView)
{
    ui->setupUi(this);
    connect(ui->copyButton, &QToolButton::clicked, this, &TeacherView::copyIDNumber);
    connect(this, &TeacherView::teacherChanged, this, &TeacherView::resetTeacher);
}

TeacherView::~TeacherView()
{
    delete ui;
}

Teacher TeacherView::getTeacher() const
{
    return container;
}

bool TeacherView::isPasswordVisible() const
{
    return ui->passwordLabel->isVisible() && ui->passwordTitle->isVisible();
}

void TeacherView::setTeacher(const Teacher &value)
{
    container = value;
    emit teacherChanged(container);
}

void TeacherView::setPasswordVisible(bool value)
{
    ui->passwordLabel->setVisible(value);
    ui->passwordTitle->setVisible(value);
}

void TeacherView::copyIDNumber()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->idView->text());
}

void TeacherView::resetTeacher()
{
    resetIdentifier();
    resetName();
    resetUserName();
    resetPassword();
    resetCreditCount();
}

void TeacherView::resetCreditCount()
{
    ui->creditCountLabel->setText(QString::number(container.getCreditCount()));
}

void TeacherView::resetIdentifier()
{
    qint64 value = container.getIdentifier();
    ui->idView->setText(value <= 0 ? "Unknown" : QString::number(value));
}

void TeacherView::resetUserName()
{
    ui->userNameLabel->setText(container.getUserName());
}

void TeacherView::resetPassword()
{
    ui->passwordLabel->setText(container.getPassword());
}

void TeacherView::resetName()
{
    ui->nameLabel->setText(container.getFullName());
}
