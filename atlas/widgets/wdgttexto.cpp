#include "wdgttexto.h"
#include "ui_wdgttexto.h"

WdgtTexto::WdgtTexto(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtTexto)
{
    ui->setupUi(this);
    registerTooltipHandler(ui->textEdit);
    registerTooltipHandler(this);
}

WdgtTexto::~WdgtTexto()
{
    delete ui;
}

QString WdgtTexto::value()
{
    return ui->textEdit->toHtml();
}

void WdgtTexto::setValue(const QString &value)
{
    ui->textEdit->setHtml(value);
}

void WdgtTexto::setNotes(const QString &newNote)
{
    ui->textEdit->setToolTip(newNote);
    setToolTip(newNote);
}

QString WdgtTexto::notes() const
{
    return toolTip();
}
