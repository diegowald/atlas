#include "wdgttexto.h"
#include "ui_wdgttexto.h"

WdgtTexto::WdgtTexto(QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtTexto)
{
    ui->setupUi(this);
}

WdgtTexto::~WdgtTexto()
{
    delete ui;
}

void WdgtTexto::on_textEdit_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
}

void WdgtTexto::on_WdgtTexto_customContextMenuRequested(const QPoint &pos)
{
    (void) pos;
    emit tooltipFired(this);
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
