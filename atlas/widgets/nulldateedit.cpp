#include "nulldateedit.h"

NullDateEdit::NullDateEdit(const QDate& date, QWidget *parent)
    : QDateEdit(date, parent)
{
    this->setSpecialValueText(" ");
    this->setDisplayFormat("dd/M/yyyy");
}


NullDateEdit::NullDateEdit(QWidget *parent)
    : QDateEdit(parent)
{
    this->setSpecialValueText(" ");
}

NullDateEdit::~NullDateEdit()
{

}

void NullDateEdit::clear()
{
    this->setDate(this->minimumDate());
}

void NullDateEdit::setDate(const QDate &date)
{
    if (!date.isValid())
        QDateEdit::setDate(this->minimumDate());
    else
        QDateEdit::setDate(date);
}

QDate NullDateEdit::nullDate() const
{
    if (date() == this->minimumDate())
        return QDate();
    return date();
}
