#include "include/data/entity.h"
#include <QDataStream>
#include <QFile>

Entity::Entity(QObject *parent) : QObject{parent} {}

Entity::Entity(const Entity &another, QObject *parent) : Entity{parent}
{
    *this = another;
}

Entity &Entity::operator=(const Entity &another)
{
    setIdentifier(another.identifier);
    return *this;
}

Entity::~Entity()
{
    commitToRecord();
}

void Entity::commitToRecord() const {}

void Entity::setIdentifier(const qint64 &identifier)
{
    this->identifier = identifier;
    emit identifierChanged(identifier);
}
qint64 Entity::getIdentifier() const
{
    return identifier;
}

bool Entity::isNull() const
{
    return identifier == -1;
}

QDataStream& operator<<(QDataStream &stream, const Entity &data)
{
    stream << data.identifier;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Entity &data)
{
    stream >> data.identifier;
    return stream;
}

bool operator==(const Entity &one, const Entity &two)
{
    return one.identifier == two.identifier;
}

bool operator!=(const Entity &one, const Entity &two)
{
    return !(one == two);
}

bool operator<(const Entity &one, const Entity &two)
{
    return one.identifier < two.identifier;
}

QDir Entity::getEntityDirectory()
{
    const QString directory = "Isfahan";
    QDir temporary = QDir::temp();
    temporary.mkdir(directory);
    temporary.cd(directory);
    return temporary;
}
