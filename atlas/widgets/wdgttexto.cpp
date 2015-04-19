#include "wdgttexto.h"
#include "ui_wdgttexto.h"

WdgtTexto::WdgtTexto(bool showNotes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtTexto)
{
    (void) showNotes;
    ui->setupUi(this);
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
}

QString WdgtTexto::notes() const
{
    return "";
}
