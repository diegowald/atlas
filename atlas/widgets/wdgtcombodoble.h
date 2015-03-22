#ifndef WDGTCOMBODOBLE_H
#define WDGTCOMBODOBLE_H

#include "customtooltipwidget.h"

namespace Ui {
class WdgtComboDoble;
}

class WdgtComboDoble : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtComboDoble(QWidget *parent = 0);
    ~WdgtComboDoble();

    void setLista1(QStringList &lista);
    void setLista2(QStringList &lista);

    QString value1();
    QString value2();
    void setValue1(const QString &newValue);
    void setValue2(const QString &newValue);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtComboDoble *ui;
};

#endif // WDGTCOMBODOBLE_H
