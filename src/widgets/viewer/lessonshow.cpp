#include "include/widgets/viewer/lessonshow.h"
#include "include/data/teacher.h"
#include "ui_lessonshow.h"

LessonShow::LessonShow(QWidget *parent) : EntityShow(parent)
{
    ui = new Ui::LessonShow;
    initialize(this);
}

LessonShow::~LessonShow()
{
    delete ui;
}

QString LessonShow::getName() const
{
    return initial.getName();
}

Entity LessonShow::getTeacher() const
{
    return initial.getTeacher();
}

quint64 LessonShow::getBranchNumber() const
{
    return initial.getBranchNumber();
}

QDateTime LessonShow::getFinalExam() const
{
    return initial.getFinalExam();
}

quint8 LessonShow::getTotalCapacity() const
{
    return initial.getTotalCapacity();
}

quint8 LessonShow::getCreditUnit() const
{
    return initial.getCreditUnit();
}

Lesson LessonShow::getLesson() const
{
    return initial;
}

void LessonShow::setName(const QString &value)
{
    initial.setName(value);
}

void LessonShow::setBranchNumber(quint64 value)
{
    initial.setBranchNumber(value);
}

void LessonShow::setFinalExam(const QDateTime &time)
{
    initial.setFinalExam(time);
}

void LessonShow::setCreditUnit(quint8 value)
{
    initial.setCreditUnit(value);
}

void LessonShow::setLesson(const Lesson &data)
{
    initial = data;
    emit lessonChanged(initial);
}

void LessonShow::resetName()
{
    ui->nameLabel->setText(initial.getName());
}

void LessonShow::resetBranchNumber()
{
    ui->branchNumberLabel->setText(QString::number(initial.getBranchNumber()));
}

void LessonShow::initialize(QWidget *target)
{
    ui->setupUi(target);
    EntityShow::initialize(ui->identifierView);
    connect(&initial, &Lesson::nameChanged, this, &LessonShow::resetName);
    connect(&initial, &Lesson::nameChanged, this, &LessonShow::nameChanged);

    connect(&initial, &Lesson::branchNumberChanged, this, &LessonShow::resetBranchNumber);
    connect(&initial, &Lesson::branchNumberChanged, this, &LessonShow::branchNumberChanged);

    connect(&initial, &Lesson::creditUnitChanged, this, &LessonShow::resetCreditUnit);
    connect(&initial, &Lesson::creditUnitChanged, this, &LessonShow::creditUnitChanged);

    connect(&initial, &Lesson::totalCapacityChanged, this, &LessonShow::resetCapacity);

    connect(&initial, &Lesson::finalExamChanged, this, &LessonShow::resetFinalExam);
    connect(&initial, &Lesson::finalExamChanged, this, &LessonShow::finalExamChanged);

    connect(this, &LessonShow::lessonChanged, this, &LessonShow::resetLesson);
}

void LessonShow::resetTeacherName()
{
    Teacher teacher = Teacher::loadFromRecord(initial.getTeacher());
    ui->teacherNameLabel->setText(teacher.getFullName());
}

void LessonShow::resetCreditUnit()
{
    ui->creditUnitLabel->setText(QString::number(initial.getCreditUnit()));
    ui->capacityLabel->setText(QString("%1 in Total (%2 remaining)").arg(initial.getTotalCapacity()).arg(initial.getLeftCapacity()));
}

void LessonShow::resetCapacity()
{
    this->setIdentifier(initial.getIdentifier());
}

void LessonShow::resetFinalExam()
{
    QDate date = initial.getFinalExam().date();
    ui->finalExamDate->setSelectedDate(date);

    QTime time = initial.getFinalExam().time();
    ui->finalExamtimeLabel->setText(QString("%1 : %2").arg(time.hour(), time.minute()));

    if(time > QTime(12, 0, 0)) {
        ui->finalExamtimeUnitLabel->setText("P.M");
    } else {
        ui->finalExamtimeUnitLabel->setText("A.M");
    }
}

void LessonShow::resetLesson()
{
    resetBranchNumber();
    resetTeacherName();
    resetCreditUnit();
    resetFinalExam();
    resetCapacity();
    resetName();
}
