#include "wdgtcheckbox.h"
#include "ui_wdgtcheckbox.h"

WdgtCheckBox::WdgtCheckBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtCheckBox)
{
    ui->setupUi(this);
}

WdgtCheckBox::~WdgtCheckBox()
{
    delete ui;
}
