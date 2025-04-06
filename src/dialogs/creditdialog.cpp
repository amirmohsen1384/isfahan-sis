#include "include/dialogs/creditdialog.h"
#include "include/errors/education.h"
#include "ui_creditdialog.h"
#include <QMessageBox>

CreditDialog::CreditDialog(Student &initial, QWidget *parent) : QDialog(parent), ui(new Ui::CreditDialog)
{
    ui->setupUi(this);
    this->target = &initial;
}

LessonList CreditDialog::getLessons() const
{
    return ui->container->getCredits();
}

void CreditDialog::accept()
{
    QMessageBox message(this);
    LessonList initial = target->getLessons();
    LessonList lessons = ui->container->getCredits();

    try {
        int newCredit = Lesson::getTotalCredit(lessons);
        int totalCredit = target->getCreditCount() + newCredit;

        if(target->getMinimumCredits() > totalCredit || target->getMaximumCredits() < totalCredit) {
            throw CreditsOutOfBoundException();
        }

        for(Lesson &target : lessons) {
            auto it = std::find_if(initial.cbegin(), initial.cend(), [&](const Lesson &element)
            {
                return element.getFinalExam() == target.getFinalExam();
            });

            if(it != initial.cend()) {
                throw OverlapException(*it, target);
            }

            this->target->addCredit(target);
        }

        QDialog::accept();
    }
    catch(const std::exception &error) {
        message.setWindowTitle("Error");
        message.setIcon(QMessageBox::Critical);
        message.setText(error.what());
        message.exec();
        return;
    }
}
