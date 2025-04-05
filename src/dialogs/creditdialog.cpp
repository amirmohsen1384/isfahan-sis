#include "include/dialogs/creditdialog.h"

CreditDialog::CreditDialog(Student &initial, QWidget *parent) : QDialog(parent)
{
    this->target = &initial;
}
