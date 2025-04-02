#ifndef TEACHERPANEL_H
#define TEACHERPANEL_H

#include <QMainWindow>

namespace Ui {
class TeacherPanel;
}

class TeacherPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherPanel(QWidget *parent = nullptr);
    ~TeacherPanel();

private:
    Ui::TeacherPanel *ui;
};

#endif // TEACHERPANEL_H
