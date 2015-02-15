#include "wdgtsino.h"
#include "ui_wdgtsino.h"

WdgtSiNo::WdgtSiNo(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtSiNo)
{
    ui->setupUi(this);
}

WdgtSiNo::~WdgtSiNo()
{
    delete ui;
}

void WdgtSiNo::on_radioSi_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

void WdgtSiNo::on_radioNo_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

void WdgtSiNo::on_WdgtSiNo_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

bool WdgtSiNo::value()
{
    return ui->radioSi->isChecked();
}
