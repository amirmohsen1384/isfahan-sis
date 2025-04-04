#include "include/widgets/views/studentview.h"
#include "include/widgets/views/teacherview.h"
#include "include/dialogs/teachereditdialog.h"
#include "include/widgets/views/lessonview.h"
#include "include/dialogs/lessoneditdialog.h"
#include "include/screens/teacherpanel.h"
#include "ui_teacherpanel.h"
#include <QMessageBox>
#include <QCloseEvent>

TeacherPanel::TeacherPanel(const Teacher &target, QWidget *parent) : TeacherPanel(parent)
{
    setTeacher(target);
}
TeacherPanel::TeacherPanel(QWidget *parent) : QMainWindow(parent), ui(new Ui::TeacherPanel)
{
    ui->setupUi(this);
    ui->tableView->setModel(&model);
    ui->viewButton->setVisible(false);
    connect(&teacher, &Teacher::lessonChanged, [&]() { toggleControlButtons(); });
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(&model, &EnrolledModel::teacherChanged, this, &TeacherPanel::resetTeacher);
}
TeacherPanel::~TeacherPanel()
{
    delete ui;
}

void TeacherPanel::closeEvent(QCloseEvent *event)
{
    event->accept();
    QGuiApplication::exit(EXIT_SUCCESS);
}

Teacher TeacherPanel::getTeacher() const
{
    return model.getTeacher();
}

void TeacherPanel::goUp()
{
    QModelIndex index = ui->tableView->rootIndex().parent();
    ui->goUpButton->setEnabled(index.isValid());
    ui->tableView->setRootIndex(index);
    if(!index.isValid()) {
        ui->lessonView->setText(QString());
    }
}

void TeacherPanel::goDown(const QModelIndex &index)
{
    if(!index.parent().isValid()) {
        ui->lessonView->setText(model.index(index.row(), 0, index.parent()).data().toString());
        ui->tableView->setRootIndex(index);
        ui->goUpButton->setEnabled(true);
    }
}

void TeacherPanel::addLesson()
{
    LessonEditDialog dialog(Lesson(), this);
    if(dialog.exec() == QDialog::Accepted) {
        Lesson target = dialog.getLesson();
        if(!target.isNull()) {
            target.commitToRecord();
            teacher.addCredit(target);
            teacher.commitToRecord();
        }
    }
}

void TeacherPanel::viewEntity()
{
    const QModelIndex &index = ui->tableView->currentIndex();
    if(!index.isValid()) {
        QMessageBox::critical(this, "Error", "The entity cannot be viewed.");
        return;
    }
    QDialog dialog(this);
    dialog.setModal(true);
    const QVariant data = index.data(Qt::UserRole);

    if(data.canConvert<Lesson>()) {
        Lesson target = qvariant_cast<Lesson>(data);
        if(!target.isNull()) {
            dialog.setWindowTitle(QString("%1 - Lesson View").arg(target.getName()));
            LessonView viewer(target, &dialog);
            dialog.exec();
        }
    }
    else if(data.canConvert<Student>()) {
        Student target = qvariant_cast<Student>(data);
        if(!target.isNull()) {
            dialog.setWindowTitle(QString("%1 - Student View").arg(target.getFullName()));
            StudentView viewer(target, &dialog);
            dialog.exec();
        }
    }
    else {
        QMessageBox::critical(this, "Error", "The entity cannot be viewed.");
    }
}

void TeacherPanel::removeEntity()
{
    const QModelIndex &index = ui->tableView->currentIndex();
    QVariant data = index.data(Qt::UserRole);

    QMessageBox message(this);
    message.setWindowTitle("Confirm");
    message.setIcon(QMessageBox::Warning);
    message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if(data.canConvert<Lesson>()) {
        Lesson target = qvariant_cast<Lesson>(data);
        message.setText("Are you sure to remove the whole lesson?");
        message.setInformativeText("<b>Note<\b>: All of the enrolled students will be removed as a consequence.");
        if(message.exec() == QMessageBox::Yes) {
            teacher.removeCredit(target);
            teacher.commitToRecord();
        }
    }

    else if(data.canConvert<Student>()) {
        Student target = qvariant_cast<Student>(data);
        message.setInformativeText("<b>Note<\b>: You cannot revert this action.");
        message.setText(QString("Are you sure to remove <b>%1<\b> from the lesson?").arg(target.getFullName()));
        if(message.exec() == QMessageBox::Yes) {
            Lesson lesson = qvariant_cast<Lesson>(index.parent().data(Qt::UserRole));
            target.removeCredit(lesson);
            target.commitToRecord();
        }
    }
}

void TeacherPanel::viewProfile()
{
    QDialog dialog(this);
    dialog.setModal(true);
    if(!teacher.isNull()) {
        dialog.setWindowTitle(QString("%1 - View Your Profile").arg(teacher.getFullName()));
        TeacherView viewer(teacher, &dialog);
        dialog.exec();
    }
}

void TeacherPanel::editProfile()
{
    TeacherEditDialog dialog(teacher, this);
    if(dialog.exec() == QDialog::Accepted) {
        setTeacher(dialog.getTeacher());
        resetTeacher();
    }
}

void TeacherPanel::setTeacher(const Teacher &teacher)
{
    model.setTeacher(teacher);
}

void TeacherPanel::resetTeacher()
{
    const QString target = teacher.getFullName();
    this->setWindowTitle(QString("%1 - Teacher Panel").arg(target));
    ui->welcomeLabel->setText(QString("Welcome back, %1!").arg(target));
}

void TeacherPanel::toggleControlButtons()
{
    ui->viewButton->setVisible(ui->tableView->currentIndex().isValid() && model.rowCount() > 0);
    ui->removeButton->setEnabled(model.rowCount() > 0 && ui->tableView->currentIndex().isValid());
}

void TeacherPanel::toggleControlButtons(const QModelIndex &index)
{
    ui->removeButton->setEnabled(index.isValid());
    ui->viewButton->setVisible(index.isValid());
}
