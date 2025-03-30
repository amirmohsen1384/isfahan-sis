#ifndef PERSONEDIT_H
#define PERSONEDIT_H

#include <QWidget>

namespace Ui {
class PersonEdit;
}

class PersonEdit : public QWidget
{
    Q_OBJECT

public:
    explicit PersonEdit(QWidget *parent = nullptr);
    ~PersonEdit();

private:
    Ui::PersonEdit *ui;
};

#endif // PERSONEDIT_H
