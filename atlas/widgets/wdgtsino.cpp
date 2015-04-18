#include "wdgtsino.h"
#include "ui_wdgtsino.h"

WdgtSiNo::WdgtSiNo(bool showNotes, QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtSiNo)
{
    ui->setupUi(this);
    registerTooltipHandler(ui->radioNo);
    registerTooltipHandler(ui->radioSi);
    registerTooltipHandler(this);
    ui->txtNotes->setVisible(showNotes);
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
    ui->txtNotes->setText(newNote);
}

QString WdgtSiNo::notes() const
{
    return ui->radioNo->toolTip();
}
