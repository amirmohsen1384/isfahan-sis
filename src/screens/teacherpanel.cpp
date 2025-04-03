#include "include/dialogs/lessondialog.h"
#include "include/screens/teacherpanel.h"
#include "ui_teacherpanel.h"

TeacherPanel::TeacherPanel(const Teacher &teacher, QWidget *parent) : TeacherPanel(parent)
{
    setTeacher(teacher);
}

TeacherPanel::TeacherPanel(QWidget *parent) : QMainWindow(parent), ui(new Ui::TeacherPanel)
{
    ui->setupUi(this);
    ui->tableView->setModel(&model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(this, &TeacherPanel::teacherChanged, this, &TeacherPanel::resetTeacher);
}

TeacherPanel::~TeacherPanel()
{
    teacher.commitToRecord();
    delete ui;
}

Teacher TeacherPanel::getTeacher() const
{
    return teacher;
}

void TeacherPanel::addLesson()
{
    LessonDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted) {
        Lesson target = dialog.getLesson();
        if(!target.isNull()) {
            teacher.addCredit(target);
            target.commitToRecord();
        }
    }
}

void TeacherPanel::setTeacher(const Teacher &teacher)
{
    this->teacher = teacher;
    emit teacherChanged(this->teacher);
}

void TeacherPanel::resetTeacher()
{
    model.setTeacher(teacher);

    ui->welcomeLabel->setText(QString("Welcome back, %1!").arg(teacher.getFullName()));
}
