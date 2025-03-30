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

    qint64 getIdentifier();
    EntityList getForbiddenEntities();

public slots:
    void setIdentifier(qint64 value);
    void setForbiddenEntities(const EntityList &entities);

private slots:
    void setRandomIdentifier(const Qt::CheckState &state);
    void validateIdentifier(const QString &text);

signals:
    void identifierRejected();
    void identifierAccepted(qint64 value);
    void entitiesChanged(const EntityList &entity);

private:
    Ui::EntityEdit *ui;
    EntityList container;
    QIntValidator *validator;
    QRandomGenerator *generator;
};

#endif // ENTITYEDIT_H
