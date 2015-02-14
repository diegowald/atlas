#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/dialoghistoriaclinica.h"
#include "model/forward.h"
#include "model/factory.h"
#include <QMessageBox>
#include <mongo/client/dbclient.h>
#include "model/historiaclinica.h"

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
    QMessageBox::information(this, "Atlas", "No implementado!");
}

void MainWindow::on_actionAnalisis_triggered()
{
    QMessageBox::information(this, "Atlas", "No implementado!");
}
