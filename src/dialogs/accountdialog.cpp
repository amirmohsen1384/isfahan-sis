#include "include/dialogs/accountdialog.h"
#include "include/errors/education.h"
#include "ui_accountdialog.h"
#include <QMessageBox>

AccountDialog::AccountDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
}

AccountDialog::~AccountDialog()
{
    delete ui;
}

void AccountDialog::accept()
{
    QMessageBox message;
    message.setWindowTitle("Error");
    message.setIcon(QMessageBox::Critical);
    QWidget *kind = ui->accountWidget->currentWidget();

    try {
        if(ui->accountWidget->currentIndex() == 0) {
            StudentEdit *editor = static_cast<StudentEdit*>(kind);
            editor->validateEditor();

            Student s = editor->getContainer();
            s.commitToRecord();
        }
        else {
            TeacherEdit *editor = static_cast<TeacherEdit*>(kind);
            editor->validateEditor();

            Teacher t = editor->getContainer();
            t.commitToRecord();
        }
    }
    catch(const InvalidPasswordException &error) {
        message.setText(error.what());
        message.setInformativeText("Your password should at least 8 characters and "
                                           "contains at least one uppercase and lowercase characters, digit and non-letter character.");
        message.exec();
        return;
    }
    catch(const InvalidIdentifierException &error) {
        message.setText(error.what());
        message.setInformativeText("Your identifier needs to be unique and should not be less than 1.");
        message.exec();
        return;
    }
    catch(std::exception const &e) {
        message.setText(e.what());
        message.exec();
        return;
    }
    QDialog::accept();
}
