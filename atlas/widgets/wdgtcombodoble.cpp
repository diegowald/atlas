#include "wdgtcombodoble.h"
#include "ui_wdgtcombodoble.h"

WdgtComboDoble::WdgtComboDoble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtComboDoble)
{
    ui->setupUi(this);
}

WdgtComboDoble::~WdgtComboDoble()
{
    delete ui;
}
