#ifndef PERSONEDIT_H
#define PERSONEDIT_H

#include <QWidget>
#include "entityedit.h"
#include "include/data/person.h"

namespace Ui {
class PersonEdit;
}

class PersonEdit : public EntityEdit
{
    Q_OBJECT
public:
    explicit PersonEdit(QWidget *parent = nullptr);
    ~PersonEdit();

    QString getFirstName() const;
    QString getLastName() const;
    QString getUserName() const;
    QString getPassword() const;

public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setUserName(const QString &value);
    void setPassword(const QString &value);

    void resetFirstName();
    void resetLastName();
    void resetUserName();
    void resetPassword();

    void toggleShowPassword(bool state);

signals:
    void firstNameChanged(const QString &value);
    void lastNameChanged(const QString &value);
    void userNameChanged(const QString &value);
    void passwordChanged(const QString &value);

protected:
    Person getInitialPerson() const;
    Person getInformationForPerson() const;

protected slots:
    void resetPerson();
    void setInitialPerson(const Person &value);
    void setInformationForPerson(const Person &value);
    virtual void initialize(QWidget *target) override;

signals:
    void initialPersonChanged(const Person &value);

private:
    Ui::PersonEdit *ui;
    Person initialPerson;
};

#endif // PERSONEDIT_H
