#ifndef STUDENTPANEL_H
#define STUDENTPANEL_H

#include <QMainWindow>

namespace Ui { class StudentPanel; }

class StudentPanel : public QMainWindow
{
    Q_OBJECT
public:
    explicit StudentPanel(QWidget *parent = nullptr);

signals:

private:
    Ui::StudentPanel *ui;
};

#endif // STUDENTPANEL_H
