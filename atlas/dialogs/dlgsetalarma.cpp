#include "dlgsetalarma.h"
#include "ui_dlgsetalarma.h"
#include "../model/alarma.h"
#include "../model/historiaclinica.h"
#include "../model/persona.h"

DlgSetAlarma::DlgSetAlarma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSetAlarma)
{
    ui->setupUi(this);
}

DlgSetAlarma::~DlgSetAlarma()
{
    delete ui;
}

void DlgSetAlarma::setData(AlarmaPtr value)
{
    ui->txtPaciente->setText(value->historiaClinica()->persona()->nombre());
    ui->txtNota->setPlainText(value->nota());
    ui->dateFechaCreacion->setDate(value->fechaCreacion());
    ui->dateFechaAlarma->setDate(value->fechaAlarma());
}

void DlgSetAlarma::updateData(AlarmaPtr alarma)
{
    alarma->setNota(ui->txtNota->toPlainText());
    alarma->setFechaCreacion(ui->dateFechaCreacion->date());
    alarma->setFechaAlarma(ui->dateFechaAlarma->date());
}
