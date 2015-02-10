#include "wdgtwithlabel.h"
#include "ui_wdgtwithlabel.h"

WdgtWithLabel::WdgtWithLabel(QWidget *parent) :
    QWidget(parent),
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
