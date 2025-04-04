#ifndef TEACHEREDITDIALOG_H
#define TEACHEREDITDIALOG_H

#include <QDialog>
#include "include/data/teacher.h"

namespace Ui { class TeacherEditDialog; }

class TeacherEditDialog : public QDialog
{
    Q_OBJECT
public:
    TeacherEditDialog(QWidget *parent = nullptr);
    TeacherEditDialog(const Teacher &teacher, QWidget *parent = nullptr);

    Teacher getTeacher() const;

public slots:
    void setTeacher(const Teacher &value);

public slots:
    void resetTeacher();
    virtual void accept() override;

signals:
    void teacherChanged(const Teacher &value);

private:
    Ui::TeacherEditDialog *ui = nullptr;
};

#endif // TEACHEREDITDIALOG_H
