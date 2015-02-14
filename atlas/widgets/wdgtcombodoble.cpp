#include "wdgtcombodoble.h"
#include "ui_wdgtcombodoble.h"

WdgtComboDoble::WdgtComboDoble(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtComboDoble)
{
    ui->setupUi(this);
}

WdgtComboDoble::~WdgtComboDoble()
{
    delete ui;
}

void WdgtComboDoble::setLista1(QStringList &lista)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(lista);
}

void WdgtComboDoble::setLista2(QStringList &lista)
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(lista);
}

void WdgtComboDoble::on_comboBox_2_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

void WdgtComboDoble::on_comboBox_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

void WdgtComboDoble::on_WdgtComboDoble_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}
