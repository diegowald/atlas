#ifndef CUSTOMTOOLTIPWIDGET_H
#define CUSTOMTOOLTIPWIDGET_H

#include <QWidget>

class CustomTooltipWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTooltipWidget(QWidget *parent /*= 0*/);
    ~CustomTooltipWidget();

protected:
    void editTooltip(QString &tooltipText);
    void registerTooltipHandler(QWidget *wdgt);
    QWidget *widgetByPosition(QPoint pt);

signals:
    void tooltipFired(QWidget *src);

public slots:
    void onTooltipEditRequested(QPoint pt);

private:
    QList<QWidget*> _widgets;
};

#endif // CUSTOMTOOLTIPWIDGET_H
