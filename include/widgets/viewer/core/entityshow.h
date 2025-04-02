#ifndef ENTITYSHOW_H
#define ENTITYSHOW_H

#include <QWidget>
#include "include/data/entity.h"

namespace Ui {
class EntityShow;
}

class EntityShow : public QWidget
{
    Q_OBJECT
public:
    explicit EntityShow(QWidget *target, QWidget *parent);
    explicit EntityShow(QWidget *parent = nullptr);
    ~EntityShow();

    qint64 getIdentifier() const;

public slots:
    void setIdentifier(qint64 value);

protected slots:
    void resetIdentifier(qint64 value);

signals:
    void identifierChanged(qint64 value);

protected:
    Entity container;
    virtual void initialize(QWidget *target);

private:
    Ui::EntityShow *ui;
};

#endif // ENTITYSHOW_H
