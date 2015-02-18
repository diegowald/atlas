#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/dialoghistoriaclinica.h"
#include "model/forward.h"
#include "model/factory.h"
#include <QMessageBox>
#include <mongo/client/dbclient.h>
#include "model/historiaclinica.h"
#include <auto_ptr.h>
#include "model/persona.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _factory = new Factory();
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
    dlg.setData(historia);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.applyData();
        mongo::DBClientConnection c;
        c.connect("localhost");
        c.insert("atlas.historias", historia->toBson());
    }
}

void MainWindow::on_pushButton_released()
{
    _historias.clear();
    QMessageBox::information(this, "Atlas", "No implementado!");
    mongo::DBClientConnection c;
    c.connect("localhost");
    std::auto_ptr<mongo::DBClientCursor> cursor = c.query("atlas.historias", mongo::BSONObj());
    while(cursor->more())
    {
        mongo::BSONObj obj = cursor->next();
        HistoriaClinicaPtr his = _factory->crearHistoria(obj);
        _historias[his->idString()] = his;
    }
    fillView();
}

void MainWindow::on_actionAnalisis_triggered()
{
    QMessageBox::information(this, "Atlas", "No implementado!");
}

void MainWindow::fillView()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    foreach (HistoriaClinicaPtr historia, _historias.values())
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(historia->persona()->nombre());
        ui->tableWidget->setItem(row, 0, item);
        item->setData(Qt::UserRole, historia->idString());
        item = new QTableWidgetItem(historia->persona()->dni());
        ui->tableWidget->setItem(row, 1, item);
        item = new QTableWidgetItem(historia->fechaPrimerConsulta().toString());
        ui->tableWidget->setItem(row, 2, item);
        item = new QTableWidgetItem(historia->fechaSegundaConsulta().toString());
        ui->tableWidget->setItem(row, 3, item);
        item = new QTableWidgetItem(historia->persona()->telefonos());
        ui->tableWidget->setItem(row, 4, item);
        item = new QTableWidgetItem(historia->persona()->email());
        ui->tableWidget->setItem(row, 5, item);
    }
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString id = ui->tableWidget->item(row, 0)->data(Qt::UserRole).toString();
    HistoriaClinicaPtr historia = _historias[id];
    DialogHistoriaClinica dlg;
    dlg.setData(historia);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.applyData();
        mongo::DBClientConnection c;
        c.connect("localhost");
        c.update("atlas.historias",
                 BSON("_id" << historia->id()),
                 historia->toBson());
    }
}
