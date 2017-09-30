#include "dialogdbserver.h"
#include "ui_dialogdbserver.h"
#include <QFileDialog>

DialogDBServer::DialogDBServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDBServer)
{
    ui->setupUi(this);
    ui->txtFileName->setText("./atlas.db");
}

DialogDBServer::~DialogDBServer()
{
    delete ui;
}

QString DialogDBServer::ip()
{
    QString _ip = "";
    if (ui->radioIPLocal->isChecked())
    {
        _ip = "127.0.0.1";
    }
    else
    {
        _ip = ui->txtRemoteServer->text();
    }
    return _ip;
}

void DialogDBServer::on_radioIPLocal_toggled(bool checked)
{
    ui->txtRemoteServer->setEnabled(!checked);
}

void DialogDBServer::on_buttonBox_accepted()
{

}

QString DialogDBServer::database()
{
    return ui->txtBase->text();
}

QString DialogDBServer::username()
{
    return ui->txtUser->text();
}

QString DialogDBServer::password()
{
    return ui->txtPassword->text();
}

void DialogDBServer::on_btnOpenFIle_clicked()
{
    QString fn = QFileDialog::getOpenFileName(this, "Seleccionar archivo", "./", "Archivos db (*.db)");
    ui->txtFileName->setText(fn);
}


QString DialogDBServer::filename()
{
    return ui->txtFileName->text();
}
