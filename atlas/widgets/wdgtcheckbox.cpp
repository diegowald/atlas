#include "wdgtcheckbox.h"
#include "ui_wdgtcheckbox.h"

WdgtCheckBox::WdgtCheckBox(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtCheckBox)
{
    ui->setupUi(this);
    registerTooltipHandler(ui->check);
    registerTooltipHandler(this);
}

WdgtCheckBox::~WdgtCheckBox()
{
    delete ui;
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
