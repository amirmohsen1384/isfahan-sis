#include "include/dialogs/lessoneditdialog.h"
#include "include/errors/education.h"
#include "ui_lessoneditdialog.h"
#include <QMessageBox>

LessonEditDialog::LessonEditDialog(const Lesson &container, QWidget *parent) : LessonEditDialog(parent)
{
    ui->lessonEdit->setDefault(container);
}

LessonEditDialog::LessonEditDialog(QWidget *parent) : QDialog(parent)
{
    ui = new Ui::LessonEditDialog;
    ui->setupUi(this);
    connect(ui->lessonEdit, &LessonEdit::defaultChanged, this, &LessonEditDialog::lessonChanged);
    connect(ui->lessonEdit, &LessonEdit::defaultChanged, [&](const Lesson &target)
    {
        QString result = target.getName();
        if(target.isNull()) {
            result = "Untitled";
        }
        this->setWindowTitle(QString("%1 - Lesson Editor").arg(result));
    });
}

Lesson LessonEditDialog::getLesson() const
{
    return ui->lessonEdit->getData();
}

void LessonEditDialog::setLesson(const Lesson &lesson)
{
    ui->lessonEdit->setDefault(lesson);
}

void LessonEditDialog::resetLesson()
{
    ui->lessonEdit->resetLesson();
}

void LessonEditDialog::accept()
{
    QMessageBox message(this);
    message.setWindowTitle("Error");
    message.setIcon(QMessageBox::Critical);
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
