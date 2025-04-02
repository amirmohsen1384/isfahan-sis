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

EntityEdit::EntityEdit(QWidget *parent) : QWidget(parent)
{
    uiEntity = new Ui::EntityEdit;
}

EntityEdit::~EntityEdit()
{
    delete uiEntity;
}

qint64 EntityEdit::getInitialEntity() const
{
    return initialEntity;
}

void EntityEdit::initialize(QWidget *target)
{
    uiEntity->setupUi(target);
    generator = QRandomGenerator::global();

    validator = new QIntValidator(this);
    validator->setBottom(1);
    uiEntity->identifierEdit->setValidator(validator);

    connect(uiEntity->identifierEdit, &QLineEdit::textChanged, this, &EntityEdit::validateIdentifier);
    connect(this, &EntityEdit::identifierAccepted, [this](qint64 value)
    {
        uiEntity->identifierEdit->setStyleSheet("color: black");
        emit identifierChanged(value);
    });
    connect(this, &EntityEdit::identifierRejected, [this]()
    {
        uiEntity->identifierEdit->setStyleSheet("color: red");
    });
    connect(this, &EntityEdit::forbiddenEntitiesChanged, [this]()
    {
        validateIdentifier(uiEntity->identifierEdit->text());
    });
}

qint64 EntityEdit::getIdentifier() const
{
    return uiEntity->identifierEdit->text().toLongLong();
}

void EntityEdit::setIdentifier(qint64 value)
{
    uiEntity->identifierEdit->setText(QString::number(value));
}

void EntityEdit::setRandomIdentifier(const Qt::CheckState &state)
{
    switch(state) {
    case Qt::Checked: {
        qint64 value = generateRandomNumber();
        uiEntity->identifierEdit->setDisabled(true);
        setIdentifier(value);
        break;
    }
    case Qt::Unchecked: {
        uiEntity->identifierEdit->setDisabled(false);
        uiEntity->identifierEdit->setText({});
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
    setIdentifier(initialEntity);
}

void EntityEdit::setInitialEntity(qint64 value)
{
    initialEntity = value;
    emit initialEntityChanged(value);
}

void EntityEdit::setForbiddenEntities(const EntityList &entities)
{
    this->container = entities;
    emit forbiddenEntitiesChanged(this->container);
}
