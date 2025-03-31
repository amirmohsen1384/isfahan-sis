#ifndef TEACHEREDIT_H
#define TEACHEREDIT_H

#include <QWidget>
#include "include/data/teacher.h"

namespace Ui {
class TeacherEdit;
}

class TeacherEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherEdit(const Teacher &initial , QWidget *parent = nullptr);
    explicit TeacherEdit(QWidget *parent = nullptr);
    ~TeacherEdit();

    QString getFirstName() const;
    
    QString getLastName() const;

    QString getUserName() const;

    QString getPassword() const;

    qint64 getIdentifier() const;

    Teacher getInitial() const;

    Teacher getInformation() const;

public slots:
    void setFirstName(const QString &value);

    void setLastName(const QString &value);

    void setUserName(const QString &value);

    void setPassword(const QString &value);

    void setIdentifier(qint64 value);

    void setInitial(const Teacher &value);

    void setInformation(const Teacher &value);

public slots:
    void resetFirstName();

    void resetLastName();

    void resetUserName();

    void resetPassword();

    void resetIdentifier();

    void resetProperties();

signals:
    void firstNameChanged(QString value);

    void lastNameChanged(QString value);

    void userNameChanged(QString value);

    void passwordChanged(QString value);

    void identifierChanged(qint64 value);

    void initialChanged(const Teacher &value);

private:
    Teacher initial;
    Ui::TeacherEdit *ui;
};

#endif // TEACHEREDIT_H
