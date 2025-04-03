#include "include/widgets/views/studentview.h"
#include "ui_studentview.h"
#include <QClipboard>

StudentView::StudentView(const Student &container, QWidget *parent) : StudentView(parent)
{
    setStudent(container);
}

StudentView::StudentView(QWidget *parent) : QWidget(parent), ui(new Ui::StudentView)
{
    ui->setupUi(this);
    connect(ui->copyButton, &QToolButton::clicked, this, &StudentView::copyIDNumber);
    connect(this, &StudentView::studentChanged, this, &StudentView::resetStudent);
}

StudentView::~StudentView()
{
    delete ui;
}

Student StudentView::getStudent() const
{
    return container;
}

bool StudentView::isPasswordVisible() const
{
    return ui->passwordLabel->isVisible() && ui->passwordTitle->isVisible();
}

void StudentView::setStudent(const Student &value)
{
    container = value;
    emit studentChanged(container);
}

void StudentView::setPasswordVisible(bool value)
{
    ui->passwordLabel->setVisible(value);
    ui->passwordTitle->setVisible(value);
}

void StudentView::copyIDNumber()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->idView->text());
}

void StudentView::resetStudent()
{
    resetIdentifier();
    resetName();
    resetScore();
    resetUserName();
    resetPassword();
    resetCreditCount();
}

void StudentView::resetCreditCount()
{
    ui->creditCountLabel->setText(QString::number(container.getCreditCount()));
}

void StudentView::resetIdentifier()
{
    qint64 value = container.getIdentifier();
    ui->idView->setText(value <= 0 ? "Unknown" : QString::number(value));
}

void StudentView::resetUserName()
{
    ui->userNameLabel->setText(container.getUserName());
}

void StudentView::resetPassword()
{
    ui->passwordLabel->setText(container.getPassword());
}

void StudentView::resetScore()
{
    ui->scoreLabel->setText(QString::number(container.getScore()));
    switch(container.getState()) {
    case Student::State::Honor: {
        ui->stateLabel->setText("Honored Student");
        ui->stateLabel->setStyleSheet("color: dark-green");
        break;
    }
    case Student::State::Normal: {
        ui->stateLabel->setText("Normal Student");
        ui->stateLabel->setStyleSheet("color: black");
        break;
    }
    case Student::State::Probation: {
        ui->stateLabel->setText("Probated Student");
        ui->stateLabel->setStyleSheet("color: dark-red");
        break;
    }
    case Student::State::Rejection: {
        ui->stateLabel->setText("Rejected Student");
        ui->stateLabel->setStyleSheet("color: black");
        break;
    }
    }
}

void StudentView::resetName()
{
    ui->nameLabel->setText(container.getFullName());
}
