#ifndef STUDENTEDITDIALOG_H
#define STUDENTEDITDIALOG_H

#include <QDialog>
#include "include/data/student.h"

namespace Ui { class StudentEditDialog; }

class StudentEditDialog : public QDialog
{
    Q_OBJECT
public:
    StudentEditDialog(const Student &container, QWidget *parent = nullptr);
    StudentEditDialog(QWidget *parent = nullptr);
    Student getStudent() const;

public slots:
    void setStudent(const Student &lesson);

public slots:
    void resetStudent();
    virtual void accept() override;

signals:
    void studentChanged(const Student &lesson);

private:
    Student container;
    Ui::StudentEditDialog *ui;
};

#endif // STUDENTEDITDIALOG_H
