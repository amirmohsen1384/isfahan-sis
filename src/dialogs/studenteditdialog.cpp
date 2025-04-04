#include "include/dialogs/studenteditdialog.h"
#include "include/errors/education.h"
#include "ui_studenteditdialog.h"
#include <QMessageBox>

StudentEditDialog::StudentEditDialog(const Student &student, QWidget *parent) : StudentEditDialog(parent)
{
    setStudent(student);
}

StudentEditDialog::StudentEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::StudentEditDialog)
{
    ui->setupUi(this);
    connect(ui->mainEditor, &StudentEdit::defaultChanged, this, &StudentEditDialog::studentChanged);
    connect(ui->mainEditor, &StudentEdit::defaultChanged, [&](const Student &Student)
    {
        QString result = Student.getFullName();
        if(Student.isNull()) {
            result = "Untitled";
        }
        setWindowTitle(QString("%1 - Edit Your Profile").arg(result));
    });
}

Student StudentEditDialog::getStudent() const
{
    return ui->mainEditor->getContainer();
}

void StudentEditDialog::setStudent(const Student &value)
{
    ui->mainEditor->setDefault(value);
}

void StudentEditDialog::resetStudent()
{
    ui->mainEditor->resetStudent();
}

void StudentEditDialog::accept()
{
    QMessageBox message(this);
    message.setWindowTitle("Error");
    message.setIcon(QMessageBox::Critical);
    try {
        ui->mainEditor->validateEditor();
        QDialog::accept();

    }
    catch(InvalidIdentifierException const &exception) {
        message.setText("You have entered an invalid ID number.");
        message.setInformativeText("ID number should be unique and differ from other students.");
        message.exec();
    }
    catch(InvalidPasswordException const &exception) {
        message.setText("This password cannot be accepted");
        message.setInformativeText("A valid password contains at least one uppercase and lowercase letter, one number, and one non-letter character.");
        message.exec();
    }
    catch(std::exception const &exception) {
        message.setText(exception.what());
        message.exec();
    }
}
