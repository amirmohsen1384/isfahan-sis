#ifndef STUDENTPANEL_H
#define STUDENTPANEL_H

#include <QMainWindow>
#include <QItemSelectionModel>
#include "include/models/studentmodel.h"

namespace Ui { class StudentPanel; }

class StudentPanel : public QMainWindow
{
    Q_OBJECT
public:
    explicit StudentPanel(const Student &student, QWidget *parent = nullptr);
    explicit StudentPanel(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void removeLesson();
    void viewLesson();
    void resetPanel();

    void viewProfile();
    void editProfile();

    void addLesson();

private slots:
    void toggleControlButtons();

private:
    StudentModel resource;
    QItemSelectionModel *selection;
    Ui::StudentPanel *ui = nullptr;
    Student &target = resource.getContainer();
};

#endif // STUDENTPANEL_H
