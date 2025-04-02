#ifndef PERSONSHOW_H
#define PERSONSHOW_H

#include "entityshow.h"
#include "include/data/person.h"

namespace Ui {
class PersonShow;
}

class PersonShow : public EntityShow
{
    Q_OBJECT
public:
    explicit PersonShow(QWidget *target, QWidget *parent);
    explicit PersonShow(QWidget *parent = nullptr);
    ~PersonShow();

    QString getFirstName() const;

    QString getLastName() const;

    QString getUserName() const;

    QString getPassword() const;

public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setUserName(const QString &value);
    void setPassword(const QString &value);

signals:
    void firstNameChanged(QString value);
    void lastNameChanged(QString value);
    void userNameChanged(QString value);
    void passwordChanged(QString value);
    void creditCountChanged(int value);

protected:
    Person container;
    virtual void initialize(QWidget *target) override;

private:
    Ui::PersonShow *ui;
};

#endif // PERSONSHOW_H
