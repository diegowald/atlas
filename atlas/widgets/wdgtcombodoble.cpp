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

QString WdgtComboDoble::value1()
{
    return ui->comboBox->currentText();
}

QString WdgtComboDoble::value2()
{
    return ui->comboBox_2->currentText();
}

void WdgtComboDoble::setValue1(const QString &newValue)
{
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(newValue));
}

void WdgtComboDoble::setValue2(const QString &newValue)
{
    ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(newValue));
}
