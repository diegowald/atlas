#ifndef WDGTSINO_H
#define WDGTSINO_H

#include "customtooltipwidget.h"

namespace Ui {
class WdgtSiNo;
}

class WdgtSiNo : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtSiNo(QWidget *parent = 0);
    ~WdgtSiNo();

private slots:
    void on_radioSi_customContextMenuRequested(const QPoint &pos);

    void on_radioNo_customContextMenuRequested(const QPoint &pos);

    void on_WdgtSiNo_customContextMenuRequested(const QPoint &pos);

private:
    Ui::WdgtSiNo *ui;
};

#endif // WDGTSINO_H
