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
    explicit StudentEdit(const Student &info, QWidget *parent = nullptr);
    explicit StudentEdit(QWidget *parent = nullptr);
    ~StudentEdit();

    QString getFirstName() const;
    QString getLastName() const;
    QString getUserName() const;
    QString getPassword() const;
    qint64 getIdentifier() const;
    float getScore() const;

    Student getContainer() const;
    Student getDefault() const;

public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setUserName(const QString &value);
    void setPassword(const QString &value);
    void setIdentifier(qint64 value);
    void setScore(float value);

    void setContainer(const Student &value);
    void setDefault(const Student &value);

public slots:
    void resetFirstName();
    void resetLastName();
    void resetUserName();
    void resetPassword();
    void resetIdentifier();
    void resetScore();
    void resetStudent();

signals:
    void defaultChanged(const Student &info);

protected slots:
    void togglePasswordShow(bool value);

private:
    Student container;
    Ui::StudentEdit *ui;
};

#endif // STUDENTEDIT_H
