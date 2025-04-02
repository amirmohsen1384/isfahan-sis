#ifndef NAMEVALIDATOR_H
#define NAMEVALIDATOR_H

#include <QValidator>

class NameValidator : public QValidator
{
    Q_OBJECT
public:
    explicit NameValidator(QObject *parent = nullptr) : QValidator(parent) {}
    virtual QValidator::State validate(QString &input, int &pos) const override;
};

#endif // NAMEVALIDATOR_H
