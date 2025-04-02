#include "include/widgets/editor/lessonedit.h"
#include "ui_lessonedit.h"
#include <QIntValidator>

LessonEdit::LessonEdit(const Lesson &lesson, QWidget *parent) : LessonEdit(parent)
{
    setInitial(lesson);
}

LessonEdit::LessonEdit(QWidget *parent) : EntityEdit(parent), ui(new Ui::LessonEdit)
{
    ui->setupUi(this);
    EntityEdit::initialize(ui->entity);

    QIntValidator *validator = new QIntValidator(this);
    ui->branchNumberEdit->setValidator(validator);
    validator->setBottom(1);

    connect(this, &LessonEdit::initialChanged, this, &LessonEdit::resetLesson);
    connect(ui->nameEdit, &QLineEdit::textChanged, this, &LessonEdit::nameChanged);
    connect(ui->creditUnitEdit, &QSpinBox::valueChanged, this, &LessonEdit::creditUnitChanged);
    connect(ui->totalCapacityEdit, &QSpinBox::valueChanged, this, &LessonEdit::totalCapacityChanged);
    connect(ui->finalExamEdit, &QDateTimeEdit::dateTimeChanged, this, &LessonEdit::finalExamChanged);
    connect(ui->branchNumberEdit, &QLineEdit::textChanged, [this](const QString &value)
    {
        emit branchNumberChanged(value.toInt());
    });
}

LessonEdit::~LessonEdit()
{
    delete ui;
}

QString LessonEdit::getName() const
{
    return ui->nameEdit->text();
}

int LessonEdit::getTotalCapacity() const
{
    return ui->totalCapacityEdit->value();
}

int LessonEdit::getCreditUnit() const
{
    return ui->creditUnitEdit->value();
}

int LessonEdit::getBranchNumber() const
{
    return ui->branchNumberEdit->text().toInt();
}

QDateTime LessonEdit::getFinalExam() const
{
    return ui->finalExamEdit->dateTime();
}

Lesson LessonEdit::getInformation() const
{
    Lesson lesson = initial;
    lesson.setName(getName());
    lesson.setFinalExam(getFinalExam());
    lesson.setCreditUnit(getCreditUnit());
    lesson.setIdentifier(getIdentifier());
    lesson.setBranchNumber(getBranchNumber());
    lesson.setTotalCapacity(getTotalCapacity());
    return lesson;
}

Lesson LessonEdit::getInitial() const
{
    return initial;
}

void LessonEdit::setName(const QString &value)
{
    ui->nameEdit->setText(value);
}

void LessonEdit::setTotalCapacity(int value)
{
    ui->totalCapacityEdit->setValue(value);
}

void LessonEdit::setCreditUnit(int value)
{
    ui->creditUnitEdit->setValue(value);
}

void LessonEdit::setBranchNumber(int value)
{
    ui->branchNumberEdit->setText(QString::number(value));
}

void LessonEdit::setFinalExam(const QDateTime &value)
{
    ui->finalExamEdit->setDateTime(value);
}

void LessonEdit::setInformation(const Lesson &value)
{
    setName(value.getName());
    setFinalExam(value.getFinalExam());
    setIdentifier(value.getIdentifier());
    setCreditUnit(value.getCreditUnit());
    setBranchNumber(value.getBranchNumber());
    setTotalCapacity(value.getTotalCapacity());
}

void LessonEdit::setInitial(const Lesson &initial)
{
    this->initial = initial;
    emit initialChanged(this->initial);
}

void LessonEdit::resetName()
{
    setName(initial.getName());
}

void LessonEdit::resetTotalCapacity()
{
    setTotalCapacity(initial.getTotalCapacity());
}

void LessonEdit::resetCreditUnit()
{
    setCreditUnit(initial.getCreditUnit());
}

void LessonEdit::resetBranchNumber()
{
    setBranchNumber(initial.getBranchNumber());
}

void LessonEdit::resetFinalExam()
{
    setFinalExam(initial.getFinalExam());
}

void LessonEdit::resetLesson()
{
    resetName();
    resetTotalCapacity();
    resetCreditUnit();
    resetBranchNumber();
    resetIdentifier();
    resetFinalExam();
}
