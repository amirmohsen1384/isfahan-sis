#include "include/widgets/views/studentview.h"
#include "include/dialogs/studenteditdialog.h"
#include "include/widgets/views/lessonview.h"
#include "include/screens/studentpanel.h"
#include "ui_studentpanel.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDialog>

StudentPanel::StudentPanel(const Student &student, QWidget *parent) : StudentPanel(parent)
{
    target = student;
    resetPanel();
}

StudentPanel::StudentPanel(QWidget *parent) : QMainWindow{parent}, ui(new Ui::StudentPanel)
{
    ui->setupUi(this);
    ui->showLessonButton->setVisible(false);
    ui->removeLessonButton->setVisible(false);
    ui->registeredLessonsView->setModel(&resource);
    connect(&target, &Student::lessonChanged, this, &StudentPanel::toggleControlButtons);
    connect(&target, &Student::lessonQueueChanged, this, &StudentPanel::toggleControlButtons);
}

void StudentPanel::closeEvent(QCloseEvent *event)
{
    event->accept();
    target.commitToRecord();
    QGuiApplication::exit();
}

void StudentPanel::removeLesson()
{
    QMessageBox message(this);
    message.setWindowTitle("Confirm");
    message.setIcon(QMessageBox::Warning);
    message.setText("Would you like to remove a lesson?");
    message.setInformativeText("This operation cannot be reverted.");
    if(message.exec() == QDialog::Accepted) {
        const QModelIndex &index = ui->registeredLessonsView->currentIndex();
        Lesson data = qvariant_cast<Lesson>(index.data(Qt::UserRole));
        if(!data.isNull()) {
            target.removeCredit(data);
            target.commitToRecord();
        }
    }
}

void StudentPanel::viewLesson()
{
    QDialog dialog(this);
    dialog.setModal(true);
    const QModelIndex &index = ui->registeredLessonsView->currentIndex();
    const Lesson &data = qvariant_cast<Lesson>(index.data(Qt::UserRole));
    if(!data.isNull()) {
        LessonView viewer(data, dialog);
        dialog.exec();
    }
}

void StudentPanel::resetPanel()
{
    const static QStringList greetings = {
        "Have a pleasure.",
        "Nice to meet you.",
        "Welcome back.",
        "How's it going?",
        "What's going on?"
    };
    const int index = QRandomGenerator::global()->bounded(0, greetings.size() - 1);
    const QString welcome = greetings.at(index);
    const QString name = target.getFullName();
    ui->welcomeLabel->setText(QString("%1, %2").arg(name).arg(welcome));
    setWindowTitle(QString("%1 - Student Panel").arg(name));
}

void StudentPanel::viewProfile()
{
    QDialog dialog(this);
    dialog.setModal(true);
    if(!target.isNull()) {
        dialog.setWindowTitle(QString("%1 - View Your Profile").arg(target.getFullName()));
        StudentView viewer(target, &dialog);
        dialog.exec();
    }
}

void StudentPanel::editProfile()
{
    StudentEditDialog dialog(target, this);
    if(dialog.exec() == QDialog::Accepted) {
        target = dialog.getStudent();
        resetPanel();
    } else {
    }
}

void StudentPanel::toggleControlButtons()
{
    ui->showLessonButton->setVisible(ui->registeredLessonsView->currentIndex().isValid() && resource.rowCount() > 0);
    ui->removeLessonButton->setVisible(resource.rowCount() > 0 && ui->registeredLessonsView->currentIndex().isValid());
}
