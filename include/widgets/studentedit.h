#ifndef STUDENTEDIT_H
#define STUDENTEDIT_H

#include <QWidget>
#include "include/data/student.h"

namespace Ui {
class StudentEdit;
}

class StudentEdit : public QWidget
{
    Q_OBJECT
public:
    explicit StudentEdit(const Student &initial, QWidget *parent = nullptr);
    explicit StudentEdit(QWidget *parent = nullptr);
    ~StudentEdit();

    QString getFirstName() const;

    QString getLastName() const;

    QString getUserName() const;

    QString getPassword() const;

    qint64 getIdentifier() const;

    float getScore() const;

    Student getInitial() const;

    Student getInformation() const;

public slots:
    void setFirstName(const QString &value);

    void setLastName(const QString &value);

    void setUserName(const QString &value);

    void setPassword(const QString &value);

    void setIdentifier(qint64 value);

    void setScore(float score);

    void setInitial(const Student &info);

    void setInformation(const Student &info);

public slots:
    void resetFirstName();

    void resetLastName();

    void resetUserName();

    void resetPassword();

    void resetIdentifier();

    void resetScore();

    void resetProperties();

signals:
    void firstNameChanged(QString value);

    void lastNameChanged(QString value);

    void userNameChanged(QString value);

    void passwordChanged(QString value);

    void identifierChanged(qint64 value);

    void scoreChanged(float value);

    void initialChanged(const Student &info);

private:
    Student initial;
    Ui::StudentEdit *ui;
};

#endif // STUDENTEDIT_H
