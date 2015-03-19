#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/dialoghistoriaclinica.h"
#include "model/forward.h"
#include "model/factory.h"
#include <QMessageBox>
#include <mongo/client/dbclient.h>
#include <mongo/db/json.h>
#include "model/historiaclinica.h"
#include <auto_ptr.h>
#include "model/persona.h"
#include "dialogs/dlglocalips.h"
#include <QDebug>
#include "model/alarma.h"

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
    dlg.setData(historia, AlarmaPtr(NULL));
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.applyData();
        mongo::DBClientConnection c;
        //c.connect("localhost");
        std::string s = "";
        for (int i = 0; i < 3000; ++i)
        {
            c.connect(connectionString().toStdString(), s);
            qDebug() << QString(historia->toBson().toString().c_str());
            c.insert("atlas.historias", historia->toBson());
            std::string err = c.getLastError();
            mongo::BSONObj errObj = c.getLastErrorDetailed();
            qDebug() << QString(err.c_str());
            qDebug() << errObj.toString().c_str();
        }
    }
}

void MainWindow::on_pushButton_released()
{
    _historias.clear();
    mongo::DBClientConnection c;
    std::string s = "";
    c.connect(connectionString().toStdString(), s);
    //c.connect("mongodb://atlas:atlas1234ds049661.mongolab.com:49661", s);
    qDebug() << s.c_str();

    mongo::BSONObj query;
    QString queryString = "";

    ui->statusBar->showMessage("Buscando registros", 2000);
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
    query = mongo::fromjson(queryString.toStdString());
    std::auto_ptr<mongo::DBClientCursor> cursor = c.query("atlas.historias", query);
    qDebug() << c.getLastError().c_str();
    mongo::BSONObj errObj = c.getLastErrorDetailed();
    qDebug() << errObj.toString().c_str();
    while(cursor->more())
    {
        mongo::BSONObj obj = cursor->next();
        if (!obj.isEmpty())
        {
            HistoriaClinicaPtr his = _factory->crearHistoria(obj);
            _historias[his->idString()] = his;
        }
    }
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

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString id = ui->tablePacientes->item(row, 0)->data(Qt::UserRole).toString();
    HistoriaClinicaPtr historia = _historias[id];
    AlarmaPtr alarma = getAlarmaPaciente(historia->id());
    DialogHistoriaClinica dlg;
    dlg.setData(historia, alarma);
    if (dlg.exec() == QDialog::Accepted)
    {
        dlg.applyData();
        mongo::DBClientConnection c;
        //c.connect("localhost");
        std::string s = "";
        c.connect(connectionString().toStdString(), s);
        c.update("atlas.historias",
                 BSON("_id" << historia->id()),
                 historia->toBson());

        AlarmaPtr alarma = dlg.alarma();
        c.update("atlas.alarmas",
                 BSON("_id" << alarma->id()),
                 alarma->toBson());
    }
}

void MainWindow::on_actionDetectar_mi_IP_triggered()
{
    DlgLocalIPs dlg;
    dlg.exec();
}

QString MainWindow::connectionString() const
{
    //return "ds049661.mongolab.com:49661/atlas -u atlas_dev -p atlas1234"; // --authenticationDatabase atlas";
    return "localhost";
}

AlarmaPtr MainWindow::getAlarmaPaciente(mongo::OID historiaID)
{
    mongo::DBClientConnection c;
    std::string s = "";
    c.connect(connectionString().toStdString(), s);
    qDebug() << s.c_str();

    ui->statusBar->showMessage("Buscando alarma", 2000);
    std::auto_ptr<mongo::DBClientCursor> cursor = c.query("atlas.alarmas", BSON("idHistoria" << historiaID));
    qDebug() << c.getLastError().c_str();
    mongo::BSONObj errObj = c.getLastErrorDetailed();
    qDebug() << errObj.toString().c_str();
    AlarmaPtr alarma;
    alarma.clear();
    while(cursor->more())
    {
        mongo::BSONObj obj = cursor->next();
        if (!obj.isEmpty())
        {
            alarma = _factory->crearAlarma(obj);
        }
    }
    return alarma;
}
