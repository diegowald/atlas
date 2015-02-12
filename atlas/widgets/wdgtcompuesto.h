#ifndef WDGTCOMPUESTO_H
#define WDGTCOMPUESTO_H

#include "customtooltipwidget.h"
#include "../model/forward.h"

namespace Ui {
class WdgtCompuesto;
}

class WdgtCompuesto : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtCompuesto(QWidget *parent = 0);
    ~WdgtCompuesto();

    void setLabel(const QString &label);
    void addPregunta(PreguntaBasePtr pregunta);

private slots:
    void on_groupBox_customContextMenuRequested(const QPoint &pos);

    void on_WdgtCompuesto_customContextMenuRequested(const QPoint &pos);

private:
    Ui::WdgtCompuesto *ui;
};

#endif // WDGTCOMPUESTO_H
