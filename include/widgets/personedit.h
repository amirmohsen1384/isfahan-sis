#ifndef PERSONEDIT_H
#define PERSONEDIT_H

#include <QWidget>
#include "include/data/person.h"

namespace Ui {
class PersonEdit;
}

class PersonEdit : public QWidget
{
    Q_OBJECT
public:
    explicit PersonEdit(const Person &initial, QWidget *parent = nullptr);
    explicit PersonEdit(QWidget *parent = nullptr);
    ~PersonEdit();

    Person getInformation() const;
    qint64 getIdentifier() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getUserName() const;
    QString getPassword() const;

    Person getInitial() const;

public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setUserName(const QString &value);
    void setPassword(const QString &value);
    void setIdentifier(const qint64 &value);
    void setInformation(const Person &value);

    void setInitial(const Person &value);

    void resetIdentifier();
    void resetFirstName();
    void resetLastName();
    void resetUserName();
    void resetPassword();

    void resetProperties();

    void toggleShowPassword(bool state);

signals:
    void firstNameChanged(const QString &value);
    void lastNameChanged(const QString &value);
    void userNameChanged(const QString &value);
    void passwordChanged(const QString &value);
    void identifierChanged(const qint64 &value);
    void initialChanged(const Person &value);

private:
    Person initial;
    Ui::PersonEdit *ui;
};

#endif // PERSONEDIT_H
