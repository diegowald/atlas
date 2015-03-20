#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/dialoghistoriaclinica.h"
#include "model/forward.h"
#include "model/factory.h"
#include <QMessageBox>

#include <mongo/db/json.h>
#include "model/historiaclinica.h"
#include <auto_ptr.h>
#include "model/persona.h"
#include "dialogs/dlglocalips.h"
#include <QDebug>
#include "model/alarma.h"
#include "db/dbmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _factory = new Factory();
    refreshAlarmas();
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
        dbManager::instance()->insertHistoria(historia);

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
    QString id = ui->tablePacientes->item(row, 0)->data(Qt::UserRole).toString();
    HistoriaClinicaPtr historia = _historias[id];
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
