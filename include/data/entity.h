#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QDir>

class Entity : public QObject
{
    Q_OBJECT

public:
    explicit Entity(QObject *parent = nullptr);
    Entity(const Entity &another, QObject *parent = nullptr);
    explicit Entity(qint64 identifier, QObject *parent = nullptr);

    Entity& operator=(const Entity &another);
    ~Entity();

    bool isNull() const;
    qint64 getIdentifier() const;

public slots:
    virtual void commitToRecord() const;
    void setIdentifier(const qint64 &identifier);

    friend QDataStream& operator<<(QDataStream &stream, const Entity &data);
    friend QDataStream& operator>>(QDataStream &stream, Entity &data);

    friend bool operator==(const Entity &one, const Entity &two);
    friend bool operator!=(const Entity &one, const Entity &two);
    friend bool operator<(const Entity &one, const Entity &two);

    static QDir getEntityDirectory();

signals:
    void identifierChanged(const qint64 &identifier);

protected:
    qint64 identifier = -1;
};

using EntityList = QList<Entity>;

QDataStream& operator<<(QDataStream &stream, const Entity &data);
QDataStream& operator>>(QDataStream &stream, Entity &data);

bool operator==(const Entity &one, const Entity &two);
bool operator!=(const Entity &one, const Entity &two);
bool operator<(const Entity &one, const Entity &two);

Q_DECLARE_METATYPE(Entity)

#endif // ENTITY_H
