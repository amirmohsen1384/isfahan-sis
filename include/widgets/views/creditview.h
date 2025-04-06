#ifndef CREDITVIEW_H
#define CREDITVIEW_H

#include <QWidget>
#include <QItemSelectionModel>
#include "include/models/lessonlistmodel.h"
#include "include/models/teachingloadmodel.h"

namespace Ui { class CreditView; }

class CreditView : public QWidget
{
    Q_OBJECT
public:
    explicit CreditView(QWidget *parent = nullptr);
    LessonList getCredits() const;

public slots:
    void resetView(int index);

    void goDeeper(const QModelIndex &index);
    void goUp();
signals:
    void viewChanged();

private:
    QItemSelectionModel *teacherSelection = nullptr;
    TeachingLoadModel teacherModel;

    QItemSelectionModel *lessonSelection = nullptr;
    LessonListModel lessonModel;

    Ui::CreditView *ui;
};

#endif // CREDITVIEW_H
