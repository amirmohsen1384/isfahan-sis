#include "include/dialogs/lessondialog.h"
#include "include/errors/education.h"
#include "ui_lessondialog.h"
#include <QMessageBox>

LessonDialog::LessonDialog(const Lesson &container, QWidget *parent) : LessonDialog(parent)
{
    ui->lessonEdit->setDefault(container);
}

LessonDialog::LessonDialog(QWidget *parent) : QDialog(parent)
{
    ui = new Ui::LessonDialog;
    ui->setupUi(this);
    connect(ui->lessonEdit, &LessonEdit::defaultChanged, this, &LessonDialog::lessonChanged);
}

Lesson LessonDialog::getLesson() const
{
    return ui->lessonEdit->getData();
}

void LessonDialog::setLesson(const Lesson &lesson)
{
    ui->lessonEdit->setDefault(lesson);
}

void LessonDialog::resetLesson()
{
    ui->lessonEdit->resetLesson();
}

void LessonDialog::accept()
{
    QMessageBox message(this);
    message.setWindowTitle("Error");
    message.setIcon(QMessageBox::Warning);
    try {
        ui->lessonEdit->validateEditor();
        QDialog::accept();
    }
    catch(InvalidIdentifierException const &exception) {
        message.setText("You have entered an invalid ID number.");
        message.setInformativeText("ID number should be unique and differ from other lessons.");
        message.exec();
    }
    catch(std::exception const &exception) {
        message.setText(exception.what());
        message.exec();
    }
}
