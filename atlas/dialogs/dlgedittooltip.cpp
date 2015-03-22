#include "dlgedittooltip.h"
#include "ui_dlgedittooltip.h"

DlgEditTooltip::DlgEditTooltip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditTooltip)
{
    ui->setupUi(this);
}

DlgEditTooltip::~DlgEditTooltip()
{
    delete ui;
}

void DlgEditTooltip::setData(const QString &value)
{
    ui->txtNota->setPlainText(value);
}

QString DlgEditTooltip::data()
{
    return ui->txtNota->toPlainText();
}
