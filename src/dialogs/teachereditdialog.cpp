#include "include/dialogs/teachereditdialog.h"
#include "include/errors/education.h"
#include "ui_teachereditdialog.h"
#include <QMessageBox>

TeacherEditDialog::TeacherEditDialog(const Teacher &teacher, QWidget *parent) : TeacherEditDialog(parent)
{
    setTeacher(teacher);
}

Teacher TeacherEditDialog::getTeacher() const
{
    return ui->mainEditor->getContainer();
}

void TeacherEditDialog::setTeacher(const Teacher &value)
{
    ui->mainEditor->setDefault(value);
}

void TeacherEditDialog::resetTeacher()
{
    ui->mainEditor->resetTeacher();
}

void TeacherEditDialog::accept()
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
        message.setInformativeText("ID number should be unique and differ from other lessons.");
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

TeacherEditDialog::TeacherEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::TeacherEditDialog)
{
    ui->setupUi(this);
    connect(ui->mainEditor, &TeacherEdit::defaultChanged, this, &TeacherEditDialog::teacherChanged);
    connect(ui->mainEditor, &TeacherEdit::defaultChanged, [&](const Teacher &teacher)
    {
        QString result = teacher.getFullName();
        if(teacher.isNull()) {
            result = "Untitled";
        }
        setWindowTitle(QString("%1 - Edit Your Profile").arg(result));
    });
}
