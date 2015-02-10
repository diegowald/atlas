#include "wdgtsino.h"
#include "ui_wdgtsino.h"

WdgtSiNo::WdgtSiNo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtSiNo)
{
    ui->setupUi(this);
}

WdgtSiNo::~WdgtSiNo()
{
    delete ui;
}
