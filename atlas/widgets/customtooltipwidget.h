#ifndef CUSTOMTOOLTIPWIDGET_H
#define CUSTOMTOOLTIPWIDGET_H

#include <QWidget>

class CustomTooltipWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTooltipWidget(QWidget *parent = 0);
    ~CustomTooltipWidget();

signals:
    void tooltipFired();

public slots:
};

#endif // CUSTOMTOOLTIPWIDGET_H
