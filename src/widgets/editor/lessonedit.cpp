#include "include/widgets/editor/lessonedit.h"
#include "ui_lessonedit.h"

LessonEdit::LessonEdit(const Lesson &container, QWidget *parent) : LessonEdit(parent)
{
    setDefault(container);
}

LessonEdit::LessonEdit(QWidget *parent) : QWidget(parent), ui(new Ui::LessonEdit)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(this);
    validator->setBottom(1);

    ui->identifierEdit->setValidator(validator);
    ui->branchNumberEdit->setValidator(validator);
    connect(this, &LessonEdit::defaultChanged, this, &LessonEdit::resetLesson);
}

LessonEdit::~LessonEdit()
{
    delete ui;
}

QString LessonEdit::getName() const
{
    return ui->nameEdit->text();
}

qint64 LessonEdit::getIdentifier() const
{
    return ui->identifierEdit->text().toLongLong();
}

int LessonEdit::getTotalCapacity() const
{
    return ui->totalCapacityEdit->value();
}

QDateTime LessonEdit::getFinalExam() const
{
    return ui->finalExamEdit->dateTime();
}

int LessonEdit::getBranchNumber() const
{
    return ui->branchNumberEdit->text().toInt();
}

int LessonEdit::getCreditUnit() const
{
    return ui->creditUnitEdit->value();
}

Lesson LessonEdit::getDefault() const
{
    return container;
}

Lesson LessonEdit::getData() const
{
    Lesson data = container;
    data.setName(this->getName());
    data.setBranchNumber(this->getBranchNumber());
    data.setFinalExam(this->getFinalExam());
    data.setCreditUnit(this->getCreditUnit());
    data.setIdentifier(this->getIdentifier());
    data.setTotalCapacity(this->getTotalCapacity());
    return data;
}

void LessonEdit::setName(const QString &value)
{
    ui->nameEdit->setText(value);
}

void LessonEdit::setTotalCapacity(int value)
{
    ui->totalCapacityEdit->setValue(value);
}

void LessonEdit::setFinalExam(const QDateTime &data)
{
    ui->finalExamEdit->setDateTime(data);
}

void LessonEdit::setIdentifier(qint64 value)
{
    ui->identifierEdit->setText(QString::number(value));
}

void LessonEdit::setBranchNumber(int value)
{
    ui->identifierEdit->setText(QString::number(value));
}

void LessonEdit::setCreditUnit(int value)
{
    ui->creditUnitEdit->setValue(value);
}

void LessonEdit::setDefault(const Lesson &value)
{
    container = value;
    emit defaultChanged(value);
}

void LessonEdit::setData(const Lesson &value)
{
    setName(value.getName());
    setBranchNumber(value.getBranchNumber());
    setFinalExam(value.getFinalExam());
    setCreditUnit(value.getCreditUnit());
    setIdentifier(value.getIdentifier());
    setTotalCapacity(value.getTotalCapacity());
}

void LessonEdit::resetName()
{
    setName(container.getName());
}

void LessonEdit::resetTotalCapacity()
{
    setTotalCapacity(container.getTotalCapacity());
}

void LessonEdit::resetFinalExam()
{
    setFinalExam(container.getFinalExam());
}

void LessonEdit::resetIdentifier()
{
    qint64 value = container.getIdentifier();
    setIdentifier(container.isNull() ? 1 : value);
}

void LessonEdit::resetBranchNumber()
{
    setBranchNumber(container.getBranchNumber());
}

void LessonEdit::resetCreditUnit()
{
    setCreditUnit(container.getCreditUnit());
}

void LessonEdit::resetLesson()
{
    resetName();
    resetBranchNumber();
    resetCreditUnit();
    resetFinalExam();
    resetTotalCapacity();
    resetIdentifier();
}
