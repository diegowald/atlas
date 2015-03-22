#include "wdgtsino.h"
#include "ui_wdgtsino.h"

WdgtSiNo::WdgtSiNo(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtSiNo)
{
    ui->setupUi(this);
    registerTooltipHandler(ui->radioNo);
    registerTooltipHandler(ui->radioSi);
    registerTooltipHandler(this);
}

WdgtSiNo::~WdgtSiNo()
{
    delete ui;
}

bool WdgtSiNo::value()
{
    return ui->radioSi->isChecked();
}

void WdgtSiNo::setValue(bool newValue)
{
    ui->radioSi->setChecked(newValue);
    ui->radioNo->setChecked(!newValue);
}

void WdgtSiNo::setNotes(const QString &newNote)
{
    ui->radioNo->setToolTip(newNote);
    ui->radioSi->setToolTip(newNote);
    setToolTip(newNote);
}

QString WdgtSiNo::notes() const
{
    return ui->radioNo->toolTip();
}
