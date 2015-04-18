#ifndef NULLDATEEDIT_H
#define NULLDATEEDIT_H

#include <QDateEdit>

class NullDateEdit : public QDateEdit
{
    Q_OBJECT
    Q_PROPERTY(QDate nullDate READ nullDate WRITE setDate USER true)

public:
    NullDateEdit(const QDate& date, QWidget *parent);
    NullDateEdit(QWidget *parent);
    virtual ~NullDateEdit();

    QDate nullDate() const;

public slots:
    void clear();
    void setDate(const QDate &date);
};

#endif // NULLDATEEDIT_H
