#include <QClipboard>
#include "ui_lessonview.h"
#include "include/data/teacher.h"
#include "include/widgets/views/lessonview.h"

LessonView::LessonView(const Lesson &lesson, QWidget *parent) : LessonView(parent)
{
    setLesson(lesson);
}

LessonView::LessonView(QWidget *parent) : QWidget(parent), ui(new Ui::LessonView)
{
    ui->setupUi(this);
    connect(this, &LessonView::lessonChanged, this, &LessonView::resetLesson);
}

LessonView::~LessonView()
{
    delete ui;
}

void LessonView::resetName()
{
    ui->nameLabel->setText(container.getName());
}

void LessonView::resetIdentifier()
{
    qint64 value = container.getIdentifier();
    ui->idView->setText(value <= 0 ? "Unknown" : QString::number(value));
}

void LessonView::resetBranchNumber()
{
    ui->branchNumberLabel->setText(QString::number(container.getBranchNumber()));
}

void LessonView::resetCreditUnit()
{
    ui->creditUnitLabel->setText(QString::number(container.getCreditUnit()));

}

void LessonView::resetTeacherName()
{
    Teacher teacher = Teacher::loadFromRecord(container.getTeacher());
    const QString name = teacher.getFullName();
    ui->teacherNameLabel->setText(name.isEmpty() ? "Not specified" : name);
}

void LessonView::resetTotalCapacity()
{
    ui->capacityLabel->setText(QString("%1 (%2 remaining)").arg(container.getTotalCapacity()).arg(container.getLeftCapacity()));
}

void LessonView::resetFinalExam()
{
    QDate date = container.getFinalExam().date();
    ui->finalExamDate->setSelectedDate(date);

    QTime time = container.getFinalExam().time();
    ui->finalExamtimeLabel->setText(time.toString("hh:mm A"));

    qint64 days = QDate::currentDate().daysTo(date);
    if(days < 0) {
        ui->daysLeftLabel->setText(QString("The final exam has been taken!"));
    }
    else if(days == 0) {
        ui->daysLeftLabel->setText(QString("Your final exam is about to be taken."));

    } else {
        ui->daysLeftLabel->setText(QString("%1 day(s) are left to the final exam.").arg(days));
    }


}

void LessonView::resetLesson()
{
    resetTotalCapacity();
    resetBranchNumber();
    resetTeacherName();
    resetIdentifier();
    resetCreditUnit();
    resetFinalExam();
    resetName();
}

void LessonView::copyIDNumber()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->idView->text());
}

Lesson LessonView::getLesson() const
{
    return container;
}

void LessonView::setLesson(const Lesson &value)
{
    container = value;
    emit lessonChanged(container);
}
