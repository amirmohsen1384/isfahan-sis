#include "include/widgets/personedit.h"
#include "ui_personedit.h"

PersonEdit::PersonEdit(QWidget *parent) : QWidget(parent), ui(new Ui::PersonEdit)
{
    ui->setupUi(this);
}

PersonEdit::~PersonEdit()
{
    delete ui;
}
