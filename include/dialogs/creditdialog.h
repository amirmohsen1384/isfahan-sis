#ifndef CREDITDIALOG_H
#define CREDITDIALOG_H

#include <QDialog>
#include "include/data/student.h"

namespace Ui { class CreditDialog; }

class CreditDialog : public QDialog
{
    Q_OBJECT
public:
    CreditDialog(Student &initial, QWidget *parent = nullptr);
    LessonList getLessons() const;

public slots:
    virtual void accept() override;

private:
    Student *target = nullptr;
    Ui::CreditDialog *ui = nullptr;
};

#endif // CREDITDIALOG_H
