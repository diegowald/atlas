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
    _historia = historia;
}

void DialogHistoriaClinica::applyData()
{
    QDate date = ui->datePrimerConsulta->date();
    ui->widgetPersona->applyData();
    _historia->setFechaPrimerConsulta(date);
    date = ui->dateSegundaConsulta->date();
    _historia->setFechaSegundaConsulta(date);
    _historia->setNumeroPaciente(ui->txtNumeroPaciente->text());
}

void DialogHistoriaClinica::setAntecedentes(QList<PreguntaBasePtr> &antecedentes)
{
    int currColumn = 0;
    int currRow = 0;
    foreach (PreguntaBasePtr pregunta, antecedentes)
    {
        ui->gridLayoutAntecedentes->addWidget(pregunta->widget(true), currRow, currColumn, 1, 1);
        currColumn++;
        if (currColumn == 3)
        {
            currRow++;
            currColumn = 0;
        }
    }
}

void DialogHistoriaClinica::setCuestionario(QList<PreguntaBasePtr> &cuestionario)
{
    int currColumn = 0;
    int currRow = 0;
    foreach (PreguntaBasePtr pregunta, cuestionario)
    {
        ui->gridLayoutCuestionario->addWidget(pregunta->widget(false), currRow, currColumn, 1, 1);
        currColumn++;
        if (currColumn == 3)
        {
            currRow++;
            currColumn = 0;
        }
    }
}
