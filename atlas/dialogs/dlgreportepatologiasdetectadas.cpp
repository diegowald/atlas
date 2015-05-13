#include "dlgreportepatologiasdetectadas.h"
#include "ui_dlgreportepatologiasdetectadas.h"

DlgReportePatologiasDetectadas::DlgReportePatologiasDetectadas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgReportePatologiasDetectadas)
{
    ui->setupUi(this);
    ui->dateFrom->setDate(QDate::currentDate().addMonths(-1));
    ui->dateTo->setDate(QDate::currentDate());
}

DlgReportePatologiasDetectadas::~DlgReportePatologiasDetectadas()
{
    delete ui;
}

QDate DlgReportePatologiasDetectadas::dateFrom()
{
    return ui->dateFrom->date();
}

QDate DlgReportePatologiasDetectadas::dateTo()
{
    return ui->dateTo->date();
}

bool DlgReportePatologiasDetectadas::filterOn1stAppt()
{
    return ui->radioFiltroPrimerConsulta->isChecked();
}
