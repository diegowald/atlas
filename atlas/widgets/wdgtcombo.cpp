#include "wdgtcombo.h"
#include "ui_wdgtcombo.h"

WdgtCombo::WdgtCombo(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtCombo)
{
    ui->setupUi(this);
}

WdgtCombo::~WdgtCombo()
{
    delete ui;
}

void WdgtCombo::setLista(QStringList &lista)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(lista);
}

void WdgtCombo::on_comboBox_customContextMenuRequested(const QPoint &pos)
{

}

void WdgtCombo::on_WdgtCombo_customContextMenuRequested(const QPoint &pos)
{

}
