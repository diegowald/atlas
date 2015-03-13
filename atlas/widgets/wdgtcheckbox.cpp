#include "wdgtcheckbox.h"
#include "ui_wdgtcheckbox.h"

WdgtCheckBox::WdgtCheckBox(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtCheckBox)
{
    ui->setupUi(this);
}

WdgtCheckBox::~WdgtCheckBox()
{
    delete ui;
}

void WdgtCheckBox::on_check_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

void WdgtCheckBox::on_WdgtCheckBox_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

bool WdgtCheckBox::value()
{
    return ui->check->isChecked();
}

void WdgtCheckBox::setValue(bool newValue)
{
    ui->check->setChecked(newValue);
}

void WdgtCheckBox::setNotes(const QString &newNote)
{
    ui->check->setToolTip(newNote);
    setToolTip(newNote);
}

QString WdgtCheckBox::notes() const
{
    return toolTip();
}
