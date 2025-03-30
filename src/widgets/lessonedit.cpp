#include "include/widgets/lessonedit.h"
#include "ui_lessonedit.h"

LessonEdit::LessonEdit(const Lesson &lesson, QWidget *parent) : LessonEdit(parent)
{
    setInitial(lesson);
}

LessonEdit::LessonEdit(QWidget *parent) : QWidget(parent), ui(new Ui::LessonEdit)
{
    ui->setupUi(this);
    connect(this, &LessonEdit::initialChanged, this, &LessonEdit::resetProperties);
    connect(ui->nameEdit, &QLineEdit::textChanged, this, &LessonEdit::nameChanged);
    connect(ui->capacityEdit, &QSpinBox::valueChanged, this, &LessonEdit::capacityChanged);
    connect(ui->creditUnitEdit, &QSpinBox::valueChanged, this, &LessonEdit::creditUnitChanged);
    connect(ui->entity, &EntityEdit::identifierAccepted, this, &LessonEdit::identifierChanged);
    connect(ui->finalExamEdit, &QDateTimeEdit::dateTimeChanged, this, &LessonEdit::finalExamChanged);
    connect(ui->branchNumberEdit, &QLineEdit::textChanged, [this](const QString &value) { emit branchNumberChanged(value.toInt()); });
}

LessonEdit::~LessonEdit()
{
    delete ui;
}

int LessonEdit::getCapacity() const
{
    return ui->capacityEdit->value();
}

QString LessonEdit::getName() const
{
    return ui->nameEdit->text();
}

int LessonEdit::getCreditUnit() const
{
    return ui->creditUnitEdit->value();
}

int LessonEdit::getBranchNumber() const
{
    return ui->branchNumberEdit->text().toInt();
}

qint64 LessonEdit::getIdentifier() const
{
    return ui->entity->getIdentifier();
}

QDateTime LessonEdit::getFinalExam() const
{
    return ui->finalExamEdit->dateTime();
}

Lesson LessonEdit::getInformation() const
{
    Lesson lesson;
    lesson.setName(getName());
    lesson.setBranchNumber(getBranchNumber());
    lesson.setTotalCapacity(getCapacity());
    lesson.setCreditUnit(getCreditUnit());
    lesson.setIdentifier(getIdentifier());
    lesson.setFinalExam(getFinalExam());
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

void LessonEdit::setCapacity(int value)
{
    ui->capacityEdit->setValue(value);
}

void LessonEdit::setCreditUnit(int value)
{
    ui->creditUnitEdit->setValue(value);
}

void LessonEdit::setBranchNumber(int value)
{
    ui->branchNumberEdit->setText(QString::number(value));
}

void LessonEdit::setIdentifier(qint64 value)
{
    ui->entity->setIdentifier(value);
}

void LessonEdit::setFinalExam(const QDateTime &value)
{
    ui->finalExamEdit->setDateTime(value);
}

void LessonEdit::setInformation(const Lesson &value)
{
    setName(value.getName());
    setBranchNumber(value.getBranchNumber());
    setCapacity(value.getTotalCapacity());
    setCreditUnit(value.getCreditUnit());
    setFinalExam(value.getFinalExam());
    setIdentifier(value.getIdentifier());
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

void LessonEdit::resetCapacity()
{
    setCapacity(initial.getTotalCapacity());
}

void LessonEdit::resetCreditUnit()
{
    setCreditUnit(initial.getCreditUnit());
}

void LessonEdit::resetBranchNumber()
{
    setBranchNumber(initial.getBranchNumber());
}

void LessonEdit::resetIdentifier()
{
    ui->entity->setIdentifier(initial.getIdentifier());
}

void LessonEdit::resetFinalExam()
{
    setFinalExam(initial.getFinalExam());
}

void LessonEdit::resetProperties()
{
    resetName();
    resetCapacity();
    resetCreditUnit();
    resetBranchNumber();
    resetIdentifier();
    resetFinalExam();
}
