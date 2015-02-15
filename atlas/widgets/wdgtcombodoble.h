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

private slots:
    void on_comboBox_2_customContextMenuRequested(const QPoint &pos);

    void on_comboBox_customContextMenuRequested(const QPoint &pos);

    void on_WdgtComboDoble_customContextMenuRequested(const QPoint &pos);

private:
    Ui::WdgtComboDoble *ui;
};

#endif // WDGTCOMBODOBLE_H
