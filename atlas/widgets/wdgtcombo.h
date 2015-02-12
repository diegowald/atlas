#ifndef WDGTCOMBO_H
#define WDGTCOMBO_H

#include "customtooltipwidget.h"
#include <QStringList>

namespace Ui {
class WdgtCombo;
}

class WdgtCombo : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtCombo(QWidget *parent = 0);
    ~WdgtCombo();

    void setLista(QStringList &lista);

private slots:
    void on_comboBox_customContextMenuRequested(const QPoint &pos);

    void on_WdgtCombo_customContextMenuRequested(const QPoint &pos);

private:
    Ui::WdgtCombo *ui;
};

#endif // WDGTCOMBO_H
