#include "wdgtcombo.h"
#include "ui_wdgtcombo.h"

WdgtCombo::WdgtCombo(QWidget *parent) :
    QWidget(parent),
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
