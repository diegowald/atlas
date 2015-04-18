#include "dialoghistoriaclinica.h"
#include "ui_dialoghistoriaclinica.h"

#include "model/historiaclinica.h"
#include "model/persona.h"
#include "model/preguntabase.h"
#include "model/preguntatexto.h"
#include "dlgsetalarma.h"
#include "model/factory.h"
#include <QScrollBar>

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

void DialogHistoriaClinica::setData(HistoriaClinicaPtr historia, AlarmaPtr alarma)
{
    QString s = "Historia clínica %1";
    setWindowTitle(s.arg(historia->persona()->nombre().length() == 0 ? "" : ("de " + historia->persona()->nombre())));
    ui->widgetPersona->setData(historia->persona());
    _esPrimerConsulta = !historia->fechaPrimerConsulta().isValid();
    ui->datePrimerConsulta->setDate(_esPrimerConsulta ? QDate::currentDate() : historia->fechaPrimerConsulta());
    ui->txt2daConsulta->setVisible(!_esPrimerConsulta);
    ui->dateSegundaConsulta->setVisible(!_esPrimerConsulta);
    if (_esPrimerConsulta)
    {
        ui->dateSegundaConsulta->setDate(QDate());
    }
    else
    {
        ui->dateSegundaConsulta->setDate(historia->fechaSegundaConsulta().isValid() ?
                                             historia->fechaSegundaConsulta() :
                                             QDate::currentDate());
    }
    ui->txtNumeroPaciente->setText(historia->numeroPaciente());
    setAntecedentes(historia->antecedentes());
    setTestKinesiologico(historia->testKinesiologico());
    setCuestionario(historia->cuestionario1erConsulta(), ui->gridPrimerConsulta);
    setCuestionario(historia->cuestionario2daConsulta(), ui->gridSegundaConsulta);
    _historia = historia;
    _alarma = alarma;
    _alarmaNueva = _alarma.isNull();

    connect(ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->scrollArea_2->verticalScrollBar(), SLOT(setValue(int)));

    connect(ui->scrollArea_2->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->scrollArea->verticalScrollBar(), SLOT(setValue(int)));

    connect(ui->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            ui->scrollArea_2->horizontalScrollBar(), SLOT(setValue(int)));

    connect(ui->scrollArea_2->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            ui->scrollArea->horizontalScrollBar(), SLOT(setValue(int)));
}

void DialogHistoriaClinica::applyData()
{
    QDate date = ui->datePrimerConsulta->date();
    ui->widgetPersona->applyData();
    applyAntecedentes();
    applyTestKinesiologico();
    applyCuestionario();
    _historia->setFechaPrimerConsulta(date);
    if (!_esPrimerConsulta)
    {
        date = ui->dateSegundaConsulta->date();
    }
    else
    {
        date = QDate();
    }
    _historia->setFechaSegundaConsulta(date);
    _historia->setNumeroPaciente(ui->txtNumeroPaciente->text());
}

void DialogHistoriaClinica::setAntecedentes(QList<PreguntaBasePtr> &antecedentes)
{
    int currColumn = 0;
    int currRow = 0;
    foreach (PreguntaBasePtr pregunta, antecedentes)
    {
        PreguntaTextoPtr p = pregunta.dynamicCast<PreguntaTexto>();
        if (!p)
        {
            //ui->gridLayoutAntecedentes->addWidget(pregunta->widget(true), currRow, currColumn, 1, 1);
            QFormLayout * layout;
            switch (currColumn)
            {
            case 0:
                layout = ui->formColumn1;
                break;
            case 1:
                layout = ui->formColumn2;
                break;
            case 2:
                layout = ui->formColumn3;
                break;
            }
            layout->addRow(pregunta->label(), pregunta->widget());
            currColumn++;
            if (currColumn == 3)
            {
                currRow++;
                currColumn = 0;
            }
        }
        else
        {
            ui->layOutTextos->addWidget(pregunta->widget(true));
        }
    }
}

void DialogHistoriaClinica::setTestKinesiologico(QList<PreguntaBasePtr> &testKinesiologico)
{
    int currColumn = 0;
    int currRow = 0;
    foreach (PreguntaBasePtr pregunta, testKinesiologico)
    {
        QFormLayout * layout;
        switch (currColumn)
        {
        case 0:
            layout = ui->formColumnKinesio1;
            break;
        case 1:
            layout = ui->formColumnKinesio2;
            break;
        case 2:
            layout = ui->formColumnKinesio3;
            break;
        }
        layout->addRow(pregunta->label(), pregunta->widget());
        currColumn++;
        if (currColumn == 3)
        {
            currRow++;
            currColumn = 0;
        }
    }
}

void DialogHistoriaClinica::setCuestionario(QList<PreguntaBasePtr> &cuestionario, QGridLayout* grid)
{
    int currColumn = 0;
    int currRow = 0;
    foreach (PreguntaBasePtr pregunta, cuestionario)
    {
        grid->addWidget(pregunta->widget(false), currRow, currColumn, 1, 1);
        currColumn++;
        if (currColumn == 3)
        {
            currRow++;
            currColumn = 0;
        }
    }
}

void DialogHistoriaClinica::applyAntecedentes()
{
    foreach (PreguntaBasePtr pregunta, _historia->antecedentes())
    {
        pregunta->applyChanges();
    }
}

void DialogHistoriaClinica::applyTestKinesiologico()
{
    foreach (PreguntaBasePtr pregunta, _historia->testKinesiologico())
    {
        pregunta->applyChanges();
    }
}

void DialogHistoriaClinica::applyCuestionario()
{
    foreach (PreguntaBasePtr pregunta, _historia->cuestionario1erConsulta())
    {
        pregunta->applyChanges();
    }
    foreach (PreguntaBasePtr pregunta, _historia->cuestionario2daConsulta())
    {
        pregunta->applyChanges();
    }
}

void DialogHistoriaClinica::on_btnAlarma_released()
{
    DlgSetAlarma dlg(this);
    if (_alarma.isNull())
    {
        _alarma = Factory::crearNuevaAlarma(_historia);
    }
    dlg.setData(_alarma);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.updateData(_alarma);
    }
}

AlarmaPtr DialogHistoriaClinica::alarma()
{
    return _alarma;
}

bool DialogHistoriaClinica::alarmaNueva() const
{
    return _alarmaNueva;
}
