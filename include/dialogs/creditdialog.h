#ifndef CREDITDIALOG_H
#define CREDITDIALOG_H

#include <QDialog>
#include "include/data/student.h"

class CreditDialog : public QDialog
{
    Q_OBJECT
public:
    CreditDialog(Student &initial, QWidget *parent = nullptr);

private:
    Student *target = nullptr;
};

#endif // CREDITDIALOG_H
