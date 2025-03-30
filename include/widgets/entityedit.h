#ifndef ENTITYEDIT_H
#define ENTITYEDIT_H

#include <QWidget>
#include <QIntValidator>
#include <QRandomGenerator>

namespace Ui {
class EntityEdit;
}

class EntityEdit : public QWidget
{
    Q_OBJECT

public:
    explicit EntityEdit(QWidget *parent = nullptr);
    ~EntityEdit();

    qint64 getIdentifier();

public slots:
    void setIdentifier(qint64 value);

private slots:
    void setRandomIdentifier(const Qt::CheckState &state);

signals:
    void identifierChanged(qint64 value);

private:
    Ui::EntityEdit *ui;
    QIntValidator *validator;
    QRandomGenerator *generator;
};

#endif // ENTITYEDIT_H
