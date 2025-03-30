#include "entityedit.h"
#include "ui_entityedit.h"

EntityEdit::EntityEdit(QWidget *parent) : QWidget(parent), ui(new Ui::EntityEdit)
{
    ui->setupUi(this);
    generator = QRandomGenerator::global();

    validator = new QIntValidator(this);
    validator->setBottom(1);
    ui->identifierEdit->setValidator(validator);

    connect(ui->identifierEdit, &QLineEdit::textChanged, [this](const QString &value)
    {
        qint64 number = value.toLongLong();
        emit identifierChanged(number);
    });
}

EntityEdit::~EntityEdit()
{
    delete ui;
}

qint64 EntityEdit::getIdentifier()
{
    return ui->identifierEdit->text().toLongLong();
}

void EntityEdit::setIdentifier(qint64 value)
{
    ui->identifierEdit->setText(QString::number(value));
}

void EntityEdit::setRandomIdentifier(const Qt::CheckState &state)
{
    switch(state) {
    case Qt::Checked: {
        qint64 value = generator->generate();
        ui->identifierEdit->setDisabled(true);
        ui->identifierEdit->setText(QString::number(value));
        break;
    }
    case Qt::Unchecked: {
        ui->identifierEdit->setDisabled(false);
        ui->identifierEdit->setText({});
        break;
    }
    }
}

