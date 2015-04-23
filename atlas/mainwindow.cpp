#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/dialoghistoriaclinica.h"
#include "model/forward.h"
#include "model/factory.h"
#include <QMessageBox>

#include <mongo/db/json.h>
#include "model/historiaclinica.h"

//#include <auto_ptr.h>
#include "model/persona.h"
#include "dialogs/dlglocalips.h"
#include <QDebug>
#include "model/alarma.h"
#include "db/dbmanager.h"
#include "dialogs/dlgsetalarma.h"

// Printing
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QTextDocument>

// Save
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _factory = new Factory();
    refreshAlarmas();
    _idHistoria = "";
    _html = "";
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
        for (int i = 0; i < 3000; ++i)
        {
            dbManager::instance()->insertHistoria(historia);
            qDebug() << "Registro " << i << " insertado.";
        }
        AlarmaPtr alarma = dlg.alarma();
        if (!alarma.isNull())
        {
            dbManager::instance()->insertAlarma(alarma);
        }
    }
}

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
    if (ui->radioPrimerConsulta->isChecked())
    {
        if (queryString.length() > 0)
            queryString += ", ";
        queryString += QString("FechaSegundaConsulta : -1");
    }
    queryString = "{ " + queryString + " }";

    _historias = dbManager::instance()->historias(queryString);
    fillView();
}

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
        QTableWidgetItem *item = new QTableWidgetItem(alarma->historiaClinica()->persona()->nombre());
        item->setData(Qt::UserRole, alarma->idString());
        ui->tableAlarmas->setItem(row, 0, item);

        item = new QTableWidgetItem(alarma->fechaAlarma().toString());
        ui->tableAlarmas->setItem(row, 1, item);
    }
}

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

void MainWindow::on_actionDetectar_mi_IP_triggered()
{
    DlgLocalIPs dlg;
    dlg.exec();
}


void MainWindow::refreshAlarmas()
{
    ui->statusBar->showMessage("Buscando alarmas", 2000);
    _alarmas = dbManager::instance()->alarmas();
    fillViewAlarmas();
}

void MainWindow::on_tableAlarmas_cellDoubleClicked(int row, int column)
{
    QString id = ui->tableAlarmas->item(row, 0)->data(Qt::UserRole).toString();
    AlarmaPtr alarma = _alarmas[id];
    DlgSetAlarma dlg;
    dlg.setData(alarma);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.updateData(alarma);
        dbManager::instance()->updateAlarma(alarma);
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
        textDoc.setHtml(_html);
        textDoc.print(printer);
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
        //QPrinter printer(QPrinter::HighResolution);
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
}
