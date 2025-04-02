#include "include/widgets/editor/core/entityedit.h"
#include "ui_entityedit.h"

qint64 EntityEdit::generateRandomNumber() const
{
    qint64 target;
    do {
        target = generator->generate();
    }
    while(std::find(container.cbegin(), container.cend(), Entity(target)) != container.cend());
    return target;
}

EntityEdit::EntityEdit(QWidget *parent) : QWidget(parent), ui(new Ui::EntityEdit)
{
    ui->setupUi(this);
    generator = QRandomGenerator::global();

    validator = new QIntValidator(this);
    validator->setBottom(1);
    ui->identifierEdit->setValidator(validator);

    connect(ui->identifierEdit, &QLineEdit::textChanged, this, &EntityEdit::validateIdentifier);
    connect(this, &EntityEdit::identifierAccepted, [this](qint64 value)
    {
        ui->identifierEdit->setStyleSheet("color: black");
        emit identifierChanged(value);
    });
    connect(this, &EntityEdit::identifierRejected, [this]()
    {
        ui->identifierEdit->setStyleSheet("color: red");
    });
    connect(this, &EntityEdit::forbiddenEntitiesChanged, [this]()
    {
        validateIdentifier(ui->identifierEdit->text());
    });
}

EntityEdit::~EntityEdit()
{
    delete ui;
}

qint64 EntityEdit::getInitial() const
{
    return initial;
}

qint64 EntityEdit::getIdentifier() const
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
        qint64 value = generateRandomNumber();
        ui->identifierEdit->setDisabled(true);
        setIdentifier(value);
        break;
    }
    case Qt::Unchecked: {
        ui->identifierEdit->setDisabled(false);
        ui->identifierEdit->setText({});
        break;
    }
    }
}

void EntityEdit::validateIdentifier(const QString &text)
{
    qint64 number = text.toLongLong();
    if(std::find(container.cbegin(), container.cend(), Entity(number)) != container.cend()) {
        emit identifierRejected();
        return;

    }
    emit identifierAccepted(number);
}

EntityList EntityEdit::getForbiddenEntities() const
{
    return container;
}

void EntityEdit::resetIdentifier()
{
    setIdentifier(initial);
}

void EntityEdit::setInitial(qint64 value)
{
    initial = value;
    emit initialChanged(value);
}

void EntityEdit::setForbiddenEntities(const EntityList &entities)
{
    this->container = entities;
    emit forbiddenEntitiesChanged(this->container);
}
