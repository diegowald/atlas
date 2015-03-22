#include "customtooltipwidget.h"
#include "../dialogs/dlgedittooltip.h"

CustomTooltipWidget::CustomTooltipWidget(QWidget *parent) : QWidget(parent)
{

}

CustomTooltipWidget::~CustomTooltipWidget()
{

}

void CustomTooltipWidget::editTooltip(QString &tooltipText)
{
    DlgEditTooltip dlg;
    dlg.setData(tooltipText);
    if (dlg.exec() == QDialog::Accepted)
    {
        tooltipText = dlg.data();
    }
}

void CustomTooltipWidget::registerTooltipHandler(QWidget *wdgt)
{
    connect(wdgt, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(onTooltipEditRequested(QPoint)));
    _widgets.append(wdgt);
}

void CustomTooltipWidget::onTooltipEditRequested(QPoint pt)
{
    QWidget *wdgt = widgetByPosition(pt);
    if (wdgt != NULL)
    {
        QString tooltipText = wdgt->toolTip();
        editTooltip(tooltipText);
        wdgt->setToolTip(tooltipText);
    }
}

QWidget* CustomTooltipWidget::widgetByPosition(QPoint pt)
{
    foreach (QWidget* wdgt, _widgets)
    {
        if (wdgt->underMouse())
            return wdgt;
    }
    return NULL;
}
