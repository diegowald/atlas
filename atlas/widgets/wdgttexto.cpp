#include "wdgttexto.h"
#include "ui_wdgttexto.h"

WdgtTexto::WdgtTexto(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtTexto)
{
    ui->setupUi(this);
}

WdgtTexto::~WdgtTexto()
{
    delete ui;
}

void WdgtTexto::on_textEdit_customContextMenuRequested(const QPoint &pos)
{

}

void WdgtTexto::on_WdgtTexto_customContextMenuRequested(const QPoint &pos)
{

}
