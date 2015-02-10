#include "wdgttexto.h"
#include "ui_wdgttexto.h"

WdgtTexto::WdgtTexto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtTexto)
{
    ui->setupUi(this);
}

WdgtTexto::~WdgtTexto()
{
    delete ui;
}
