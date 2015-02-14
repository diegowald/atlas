#include "wdgtwithlabel.h"
#include "ui_wdgtwithlabel.h"

WdgtWithLabel::WdgtWithLabel(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtWithLabel)
{
    ui->setupUi(this);
}

WdgtWithLabel::~WdgtWithLabel()
{
    delete ui;
}

void WdgtWithLabel::addWidget(const QString &label, QWidget *widget)
{
    ui->formLayout->addRow(label, widget);
}

void WdgtWithLabel::on_WdgtWithLabel_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}
