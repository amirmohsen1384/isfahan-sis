#include "include/dialogs/accountdialog.h"
#include "ui_accountdialog.h"

AccountDialog::AccountDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
}

AccountDialog::~AccountDialog()
{
    delete ui;
}

void AccountDialog::accept()
{
    QWidget *kind = ui->accountWidget->currentWidget();
    if(ui->accountWidget->currentIndex() == 0) {
        StudentEdit *editor = static_cast<StudentEdit*>(kind);
        Student s = editor->getContainer();
        s.commitToRecord();

    } else {
        TeacherEdit *editor = static_cast<TeacherEdit*>(kind);
        Teacher t = editor->getContainer();
        t.commitToRecord();

    }
    QDialog::accept();
}
