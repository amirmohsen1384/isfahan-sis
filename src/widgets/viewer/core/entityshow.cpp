#include "entityshow.h"
#include "ui_entityshow.h"

EntityShow::EntityShow(QWidget *target, QWidget *parent) : QWidget(parent)
{
    ui = new Ui::EntityShow;
    initialize(target);
}
EntityShow::EntityShow(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::EntityShow;
}

EntityShow::~EntityShow()
{
    delete ui;
}

qint64 EntityShow::getIdentifier() const
{
    return ui->identifierShow->text().toLong();
}

void EntityShow::setIdentifier(qint64 value)
{
    ui->identifierShow->setText(QString::number(value));
}

void EntityShow::resetIdentifier(qint64 value)
{

}

void EntityShow::initialize(QWidget *target)
{
    ui->setupUi(target);
    connect(ui->identifierShow, &QLineEdit::textChanged, [&](const QString &text) { emit identifierChanged(text.toLong()); });
}
