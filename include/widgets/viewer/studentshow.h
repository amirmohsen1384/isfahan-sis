#ifndef STUDENTSHOW_H
#define STUDENTSHOW_H

#include <QWidget>

namespace Ui {
class StudentShow;
}

class StudentShow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentShow(QWidget *parent = nullptr);
    ~StudentShow();

private:
    Ui::StudentShow *ui;
};

#endif // STUDENTSHOW_H
