#ifndef STUDENTEDIT_H
#define STUDENTEDIT_H

#include <QWidget>
#include "include/data/student.h"

namespace Ui {
class StudentEdit;
}

class StudentEdit : public QWidget
{
    Q_OBJECT
public:
    explicit StudentEdit(const Student &initial, QWidget *parent = nullptr);
    explicit StudentEdit(QWidget *parent = nullptr);
    ~StudentEdit();

    float getScore() const;

    Student getInitial() const;
    Student getInformation() const;

public slots:
    void resetScore();
    void resetProperties();

    void setScore(float score);

    void setInitial(const Student &info);
    void setInformation(const Student &info);

signals:
    void scoreChanged(float value);

    void initialChanged(const Student &info);

private:
    Student initial;
    Ui::StudentEdit *ui;
};

#endif // STUDENTEDIT_H
