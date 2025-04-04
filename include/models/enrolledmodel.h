#ifndef ENROLLEDMODEL_H
#define ENROLLEDMODEL_H

#include "core/entityitem.h"
#include <QFileSystemWatcher>
#include <QAbstractItemModel>
#include "include/data/lesson.h"
#include "include/data/student.h"
#include "include/data/teacher.h"
#include "core/lecturetreemodel.h"

class EnrolledModel : public LectureTreeModel
{
    Q_OBJECT

public:
    explicit EnrolledModel(const Teacher &teacher, QObject *parent = nullptr);
    explicit EnrolledModel(QObject *parent = nullptr);
    Q_DISABLE_COPY_MOVE(EnrolledModel)

    Teacher getTeacher() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void setTeacher(const Teacher &teacher);

signals:
    void teacherChanged(const Teacher &value);

protected:
    virtual void setupModel() override;

private:
    Teacher target;
    friend class TeacherPanel;
};

#endif // ENROLLEDMODEL_H
