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

    Teacher getInitial() const;

public slots:
    void setInitial(const Teacher &value);
    void resetProperties();

signals:
    void initialChanged(const Teacher &value);

private:
    Teacher initial;
    Ui::TeacherEdit *ui;
};

#endif // TEACHEREDIT_H
