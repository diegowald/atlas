#ifndef WDGTTEXTO_H
#define WDGTTEXTO_H

#include "customtooltipwidget.h"

namespace Ui {
class WdgtTexto;
}

class WdgtTexto : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtTexto(QWidget *parent = 0);
    ~WdgtTexto();

    QString value();
    void setValue(const QString &value);

private slots:
    void on_textEdit_customContextMenuRequested(const QPoint &pos);

    void on_WdgtTexto_customContextMenuRequested(const QPoint &pos);

private:
    Ui::WdgtTexto *ui;
};

#endif // WDGTTEXTO_H
