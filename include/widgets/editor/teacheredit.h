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
    explicit TeacherEdit(const Teacher &info, QWidget *parent = nullptr);
    explicit TeacherEdit(QWidget *parent = nullptr);
    ~TeacherEdit();

    QString getFirstName() const;
    QString getLastName() const;
    QString getUserName() const;
    QString getPassword() const;
    qint64 getIdentifier() const;
    Teacher getContainer() const;
    Teacher getDefault() const;

    void validateEditor() const;

public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setUserName(const QString &value);
    void setPassword(const QString &value);
    void setIdentifier(qint64 value);
    void setContainer(const Teacher &value);
    void setDefault(const Teacher &value);

public slots:
    void resetFirstName();
    void resetLastName();
    void resetUserName();
    void resetPassword();
    void resetIdentifier();
    void resetTeacher();

signals:
    void defaultChanged(const Teacher &info);

protected slots:
    void togglePasswordShow(bool value);

private:
    Teacher container;
    Ui::TeacherEdit *ui;
};

#endif // TEACHEREDIT_H
