#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/dialoghistoriaclinica.h"
#include "model/forward.h"
#include "model/factory.h"
#include <QMessageBox>

#ifdef USEMONGO
#include <mongo/db/json.h>
#else
#endif

#include "model/historiaclinica.h"

#include "model/persona.h"
#include "dialogs/dlglocalips.h"
#include <QDebug>
#include "model/alarma.h"
#ifdef USEMONGO
#include "db/dbmanager.h"
#else
#include "db/dbrestmanaget.h"
#endif
#include "dialogs/dlgsetalarma.h"

// Printing
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QTextDocument>

// Save
#include <QFile>

// Coloring
#include "util/resaltadortexto.h"

// Reporting
#include "dialogs/dlgreportepatologiasdetectadas.h"
#include "reporting/reports.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef USEMONGO
#else
    connect(DBRestManager::instance(), &DBRestManager::alarmaReturned, this, &MainWindow::on_alarmaReturned);

    //connect(DBRestManager::instance(), &DBRestManager::historiaReturned, this, &MainWindow::on_historiaReturned);
    connect(DBRestManager::instance(), &DBRestManager::historiasReturned,  this, &MainWindow::on_historiasReturned);
    connect(DBRestManager::instance(), &DBRestManager::alarmasReturned, this, &MainWindow::on_alarmasReturned);

    connect(DBRestManager::instance(), &DBRestManager::historiaInserted, this, &MainWindow::on_historiaInserted);
    connect(DBRestManager::instance(), &DBRestManager::historiaUpdated, this, &MainWindow::on_historiaUpdated);

    connect(DBRestManager::instance(), &DBRestManager::alarmaInserted, this, &MainWindow::on_alarmaInserted);
    connect(DBRestManager::instance(), &DBRestManager::alarmaUpdated, this, &MainWindow::on_alarmaUpdated);

    connect(DBRestManager::instance(), &DBRestManager::existeDNIReturned, this, &MainWindow::on_existeDNIReturned);
#endif

    _factory = new Factory();
    refreshAlarmas();
    _idHistoria = "";
    _html = "";
    ui->actionImprimir_Historia_Clinica->setEnabled(false);
    ui->actionVista_PreviaHistoriaClinica->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _factory;
}

void MainWindow::on_actionNuevaHistoriaClinica_triggered()
{
    HistoriaClinicaPtr historia = _factory->crearNuevaHistoriaClinica();
    DialogHistoriaClinica dlg;
    dlg.setData(historia, AlarmaPtr(NULL));
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.applyData();
#ifdef USEMONGO
        dbManager::instance()->insertHistoria(historia);
#else
        DBRestManager::instance()->insertHistoria(historia);
#endif
        AlarmaPtr alarma = dlg.alarma();
        if (!alarma.isNull())
        {
#ifdef USEMONGO
            dbManager::instance()->insertAlarma(alarma);
#else
            DBRestManager::instance()->insertAlarma(alarma);
#endif
        }
    }
}

#ifndef USEMONGO
void MainWindow::on_historiaInserted(HistoriaClinicaPtr historia, bool error)
{

}
#endif

#ifdef USEMONGO
void MainWindow::on_pushButton_released()
{
    _historias.clear();
    ui->statusBar->showMessage("Buscando registros", 2000);
    _idHistoria = "";
    _html = "";
    QString queryString = "";
    if (ui->txtNombre->text().trimmed().length() > 0)
    {
        queryString = QString("$text : { $search : \"%1\" }").arg(ui->txtNombre->text().trimmed());
    }
    if (ui->txtDNI->text().trimmed().length() > 0)
    {
        if (queryString.length() > 0)
            queryString += ", ";
        queryString += QString("'persona.dni' : \"%1\"").arg(ui->txtDNI->text().trimmed());
    }
    if (ui->txtLocalidad->text().trimmed().length() > 0)
    {
        if (queryString.length() > 0)
            queryString += ", ";
        //queryString += QString("'persona.localidad' : { $regex : /^%1/i }").arg(ui->txtLocalidad->text().trimmed());
        queryString += QString("'persona.localidad' :  /^%1/i ").arg(ui->txtLocalidad->text().trimmed());
    }
    if (ui->radioPrimerConsulta->isChecked())
    {
        if (queryString.length() > 0)
            queryString += ", ";
        queryString += QString("FechaSegundaConsulta : -1");
    }
    queryString = "{ " + queryString + " }";

    qDebug() << queryString;
    _historias = dbManager::instance()->historias(queryString);
    fillView();
}
#else
void MainWindow::on_pushButton_released()
{
    _historias.clear();
    ui->statusBar->showMessage("Buscando registros", 2000);
    _idHistoria = "";
    _html = "";
    QString queryString = "";
    if (ui->txtNombre->text().trimmed().length() > 0)
    {
        queryString = QString("$text : { $search : \"%1\" }").arg(ui->txtNombre->text().trimmed());
    }
    if (ui->txtDNI->text().trimmed().length() > 0)
    {
        if (queryString.length() > 0)
            queryString += ", ";
        queryString += QString("'persona.dni':\"%1\"").arg(ui->txtDNI->text().trimmed());
    }
    if (ui->txtLocalidad->text().trimmed().length() > 0)
    {
        if (queryString.length() > 0)
            queryString += ", ";
        //queryString += QString("'persona.localidad':{$regex:/^%1/i}").arg(ui->txtLocalidad->text().trimmed());
        queryString += QString("'persona.localidad': /^%1/i").arg(ui->txtLocalidad->text().trimmed());
    }
    if (ui->radioPrimerConsulta->isChecked())
    {
        if (queryString.length() > 0)
            queryString += ", ";
        queryString += QString("FechaSegundaConsulta:-1");
    }
    queryString = "{" + queryString + "}";

    qDebug() << queryString;
    DBRestManager::instance()->historias(queryString);
}

void MainWindow::on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias, bool error)
{
    if (!error)
        _historias = historias;
    else
        _historias.clear();
    fillView();
}
#endif

void MainWindow::on_actionAnalisis_triggered()
{
    QMessageBox::information(this, "Atlas", "No implementado!");
}

void MainWindow::fillView()
{
    QString recCount = "Se encontraton %1 registros.";
    ui->statusBar->showMessage(recCount.arg(_historias.count()), 2000);
    ui->tablePacientes->clearContents();
    ui->tablePacientes->setRowCount(0);
    foreach (HistoriaClinicaPtr historia, _historias.values())
    {
        int row = ui->tablePacientes->rowCount();
        ui->tablePacientes->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(historia->persona()->nombre());
        ui->tablePacientes->setItem(row, 0, item);
        item->setData(Qt::UserRole, historia->idString());
        item = new QTableWidgetItem(historia->persona()->dni());
        ui->tablePacientes->setItem(row, 1, item);
        item = new QTableWidgetItem(historia->fechaPrimerConsulta().toString());
        ui->tablePacientes->setItem(row, 2, item);
        item = new QTableWidgetItem(historia->fechaSegundaConsulta().toString());
        ui->tablePacientes->setItem(row, 3, item);
        item = new QTableWidgetItem(historia->persona()->telefonos());
        ui->tablePacientes->setItem(row, 4, item);
        item = new QTableWidgetItem(historia->persona()->email());
        ui->tablePacientes->setItem(row, 5, item);
    }
}

void MainWindow::fillViewAlarmas()
{
    ui->tableAlarmas->clearContents();
    ui->tableAlarmas->setRowCount(0);
    foreach (AlarmaPtr alarma, _alarmas)
    {
        int row = ui->tableAlarmas->rowCount();
        ui->tableAlarmas->insertRow(row);

        QTableWidgetItem *item = new QTableWidgetItem("");
        if (!alarma->historiaClinica().isNull() && !alarma->historiaClinica()->persona().isNull())
        {
            item->setText(alarma->historiaClinica()->persona()->nombre());
        }
        item->setData(Qt::UserRole, alarma->idString());
        ui->tableAlarmas->setItem(row, 0, item);

        item = new QTableWidgetItem(alarma->fechaAlarma().toString());
        ui->tableAlarmas->setItem(row, 1, item);
    }
}

#ifdef USEMONGO
void MainWindow::on_tablePacientes_cellDoubleClicked(int row, int column)
{
    _idHistoria = ui->tablePacientes->item(row, 0)->data(Qt::UserRole).toString();
    HistoriaClinicaPtr historia = _historias[_idHistoria];
    AlarmaPtr alarma = dbManager::instance()->getAlarmaPaciente(historia->id());

    DialogHistoriaClinica dlg;
    dlg.setData(historia, alarma);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.applyData();
        dbManager::instance()->updateHistoria(historia);

        AlarmaPtr alarma = dlg.alarma();
        if (!alarma.isNull())
        {
            if (dlg.alarmaNueva())
            {
                dbManager::instance()->insertAlarma(alarma);
            }
            else
            {
                dbManager::instance()->updateAlarma(alarma);
            }
        }
    }
}
#else
void MainWindow::on_tablePacientes_cellDoubleClicked(int row, int column)
{
    _idHistoria = ui->tablePacientes->item(row, 0)->data(Qt::UserRole).toString();
    HistoriaClinicaPtr historia = _historias[_idHistoria];
    DBRestManager::instance()->getAlarmaPaciente(_idHistoria);
}


void MainWindow::on_alarmaReturned(AlarmaPtr alarma, bool error)
{
    if ((_idHistoria == "") || error)
        return;

    HistoriaClinicaPtr historia = _historias[_idHistoria];

    DialogHistoriaClinica dlg;
    dlg.setData(historia, alarma);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.applyData();
        DBRestManager::instance()->updateHistoria(historia);

        AlarmaPtr alarma = dlg.alarma();
        if (!alarma.isNull())
        {
            if (dlg.alarmaNueva())
            {
                DBRestManager::instance()->insertAlarma(alarma);
            }
            else
            {
                DBRestManager::instance()->updateAlarma(alarma);
            }
        }
    }
}

void MainWindow::on_historiaUpdated(HistoriaClinicaPtr historia, bool error)
{
    refreshAlarmas();
    on_pushButton_released();
}
#endif

void MainWindow::on_actionDetectar_mi_IP_triggered()
{
    DlgLocalIPs dlg;
    dlg.exec();
}


#ifdef USEMONGO
void MainWindow::refreshAlarmas()
{
    ui->statusBar->showMessage("Buscando alarmas", 2000);
    _alarmas = dbManager::instance()->alarmas();
    fillViewAlarmas();
}
#else
void MainWindow::refreshAlarmas()
{
    ui->statusBar->showMessage("Buscando alarmas", 2000);
    DBRestManager::instance()->alarmas();
}

void MainWindow::on_alarmasReturned(QMap<QString, AlarmaPtr> alarmas, bool error)
{
    if (!error)
        _alarmas = alarmas;
    else
        _alarmas.clear();
    fillViewAlarmas();
}
#endif


void MainWindow::on_tableAlarmas_cellDoubleClicked(int row, int column)
{
    QString id = ui->tableAlarmas->item(row, 0)->data(Qt::UserRole).toString();
    AlarmaPtr alarma = _alarmas[id];
    DlgSetAlarma dlg;
    dlg.setData(alarma);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.updateData(alarma);
#ifdef USEMONGO
        dbManager::instance()->updateAlarma(alarma);
#else
        DBRestManager::instance()->updateAlarma(alarma);
#endif
    }
    refreshAlarmas();
}

void MainWindow::on_actionImprimir_Historia_Clinica_triggered()
{
    if (0 < _idHistoria.length())
    {
        HistoriaClinicaPtr historia = _historias[_idHistoria];
        // Prints ActiveWindow
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dlg(&printer, this);
        if (dlg.exec() == QDialog::Accepted)
        {
            _html = historia->toHtml();
            // Print
            print(&printer);
        }
    }
}

void MainWindow::print(QPrinter *printer)
{
    if (0 < _html.length())
    {
        QTextDocument textDoc;
        ResaltadorTexto resaltador(&textDoc);
        textDoc.setHtml(_html);
        textDoc.print(printer);
        (void)resaltador;
    }
}

void MainWindow::on_actionVista_PreviaHistoriaClinica_triggered()
{
    if (0 < _idHistoria.length())
    {
        HistoriaClinicaPtr historia = _historias[_idHistoria];
        _html = historia->toHtml();
        QFile file("diego.html");
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << _html;
        file.close();
        QPrinter printer;
        QPrintPreviewDialog dlg(&printer, this);
        connect (&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
        dlg.setWindowState(dlg.windowState() | Qt::WindowMaximized);
        dlg.exec();
    }
}

void MainWindow::on_tablePacientes_itemSelectionChanged()
{
    _idHistoria = ui->tablePacientes->item(ui->tablePacientes->currentRow(), 0)->data(Qt::UserRole).toString();
    ui->actionImprimir_Historia_Clinica->setEnabled(true);
    ui->actionVista_PreviaHistoriaClinica->setEnabled(true);
}

void MainWindow::on_actionContabilizacion_Patologias_entre_Fechas_triggered()
{
    DlgReportePatologiasDetectadas dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        QDate dateFrom = dlg.dateFrom();
        QDate dateTo = dlg.dateTo();
        bool filterOn1stAppt = dlg.filterOn1stAppt();

        Reports rpt;
        ui->statusBar->showMessage("Generando reporte", 3000);
        QDialog *dlgReporte = rpt.runContabilizacionPatologiasEntreFechas(dateFrom, dateTo, filterOn1stAppt, this);
        dlgReporte->exec();
        dlgReporte->deleteLater();
    }
}





void MainWindow::on_alarmaInserted(AlarmaPtr alarma, bool error)
{
}

void MainWindow::on_alarmaUpdated(AlarmaPtr alarma, bool error)
{
}

void MainWindow::on_existeDNIReturned(const QString &dni, const QString &personaID, bool exists)
{
}
