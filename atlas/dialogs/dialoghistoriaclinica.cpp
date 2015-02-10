#include "dialoghistoriaclinica.h"
#include "ui_dialoghistoriaclinica.h"

#include "model/historiaclinica.h"
#include "model/preguntabase.h"

DialogHistoriaClinica::DialogHistoriaClinica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHistoriaClinica)
{
    ui->setupUi(this);
}

DialogHistoriaClinica::~DialogHistoriaClinica()
{
    delete ui;
}

void DialogHistoriaClinica::setData(HistoriaClinicaPtr historia)
{
    ui->widgetPersona->setData(historia->persona());
    ui->datePrimerConsulta->setDate(historia->fechaPrimerConsulta());
    ui->dateSegundaConsulta->setDate(historia->fechaSegundaConsulta());
    ui->txtNumeroPaciente->setText(historia->numeroPaciente());
    setAntecedentes(historia->antecedentes());
    setCuestionario(historia->cuestionario());
}

void DialogHistoriaClinica::setAntecedentes(QList<PreguntaBasePtr> &antecedentes)
{
    int count = antecedentes.count();
    int currColumn = 0;
    int currRow = 0;
    foreach (PreguntaBasePtr pregunta, antecedentes)
    {
        ui->gridLayoutAntecedentes->addWidget(pregunta->widget(true), currRow, currColumn, 1, 1);
        currColumn++;
        if (currColumn == 4)
        {
            currRow++;
            currColumn = 0;
        }
    }
}

void DialogHistoriaClinica::setCuestionario(QList<PreguntaBasePtr> &cuestionario)
{
}
