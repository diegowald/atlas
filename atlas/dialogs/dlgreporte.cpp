#include "dlgreporte.h"
#include "ui_dlgreporte.h"

DlgReporte::DlgReporte(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgReporte)
{
    ui->setupUi(this);
    ui->txtReporte->setReadOnly(true);
}

DlgReporte::~DlgReporte()
{
    delete ui;
}

void DlgReporte::setReportData(const QString &html)
{
    ui->txtReporte->setHtml(html);
}
