#include "include/widgets/views/creditview.h"
#include "ui_creditview.h"

CreditView::CreditView(QWidget *parent) : QWidget{parent}, ui{new Ui::CreditView}
{
    ui->setupUi(this);

    ui->lessonViewTable->setModel(&lessonModel);
    ui->teachingLoadView->setModel(&teacherModel);

    lessonSelection = ui->lessonViewTable->selectionModel();
    teacherSelection = ui->teachingLoadView->selectionModel();

    ui->teachingLoadView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teachingLoadView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->lessonViewTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->lessonViewTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

LessonList CreditView::getCredits() const
{
    LessonList container;
    QModelIndexList indices;
    switch(ui->widgets->currentIndex()) {
    case 0: {
        indices = lessonSelection->selectedRows();
        break;
    }
    case 1: {
        const QModelIndexList &rows = teacherSelection->selectedRows();
        for(const QModelIndex &index : rows) {
            if(index.parent().isValid()) {
                indices.append(index);
            }
        }
        break;
    }
    }
    for(const QModelIndex &index : indices) {
        const Lesson &lesson = qvariant_cast<Lesson>(index.data(Qt::UserRole));
        if(!lesson.isNull()) {
            container.append(lesson);
        }
    }
    return container;
}

void CreditView::resetView(int index)
{
    ui->widgets->setCurrentIndex(index);
    teacherSelection->clear();
    lessonSelection->clear();
    emit viewChanged();
}

void CreditView::goDeeper(const QModelIndex &index)
{
    if(!index.parent().isValid()) {
        ui->teacherNameView->setText(index.model()->index(index.row(), 0).data().toString());
        ui->goUpButton->setEnabled(ui->teachingLoadView->rootIndex().parent().isValid());
        ui->teachingLoadView->setRootIndex(index);
        teacherSelection->clear();
    }
}

void CreditView::goUp()
{
    const QModelIndex &index = ui->teachingLoadView->rootIndex();
    const QModelIndex &parent = index.parent();
    ui->goUpButton->setEnabled(parent.isValid());
    ui->teachingLoadView->setRootIndex(parent);
    ui->teacherNameView->setText(QString());
    teacherSelection->clear();
}
