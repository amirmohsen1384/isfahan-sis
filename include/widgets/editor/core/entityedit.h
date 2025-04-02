#ifndef ENTITYEDIT_H
#define ENTITYEDIT_H

#include <QWidget>
#include <QIntValidator>
#include <QRandomGenerator>
#include "include/data/entity.h"

namespace Ui {
class EntityEdit;
}

class EntityEdit : public QWidget
{
    Q_OBJECT
private:
    qint64 generateRandomNumber() const;

public:
    explicit EntityEdit(QWidget *parent = nullptr);
    ~EntityEdit();

    qint64 getIdentifier() const;
    EntityList getForbiddenEntities() const;

public slots:
    void resetIdentifier();
    void setIdentifier(qint64 value);
    void setForbiddenEntities(const EntityList &entities);

signals:
    void identifierChanged(qint64 value);
    void forbiddenEntitiesChanged(const EntityList &entity);

private slots:
    void validateIdentifier(const QString &text);
    void setRandomIdentifier(const Qt::CheckState &state);

protected:
    qint64 getInitial() const;
    virtual void initialize(QWidget *target);

protected slots:
    void setInitial(qint64 value);

signals:
    void identifierAccepted(qint64 value);
    void initialChanged(qint64 value);
    void identifierRejected();

private:
    qint64 initial;
    Ui::EntityEdit *ui;
    EntityList container;
    QIntValidator *validator;
    QRandomGenerator *generator;
};

#endif // ENTITYEDIT_H
