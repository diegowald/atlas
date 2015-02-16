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
        _historias.append(_factory->crearHistoria(obj));
    }
    fillView();
}

void MainWindow::on_actionAnalisis_triggered()
{
    QMessageBox::information(this, "Atlas", "No implementado!");
}

void MainWindow::fillView()
{
    ui->tableWidget->clear();
    foreach (HistoriaClinicaPtr historia, _historias)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(historia->persona()->nombre());
        ui->tableWidget->setItem(row, 0, item);
    }
}
