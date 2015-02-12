#ifndef WDGTWITHLABEL_H
#define WDGTWITHLABEL_H

#include "customtooltipwidget.h"

namespace Ui {
class WdgtWithLabel;
}

class WdgtWithLabel : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtWithLabel(QWidget *parent = 0);
    ~WdgtWithLabel();
    void addWidget(const QString &label, QWidget* widget);

private slots:
    void on_WdgtWithLabel_customContextMenuRequested(const QPoint &pos);

private:
    Ui::WdgtWithLabel *ui;
};

#endif // WDGTWITHLABEL_H
