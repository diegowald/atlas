#include "dialogdbserver.h"
#include "ui_dialogdbserver.h"

DialogDBServer::DialogDBServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDBServer)
{
    ui->setupUi(this);
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
        _ip = ui->txtRemoteDB->text();
    }
    return _ip;
}

void DialogDBServer::on_radioIPLocal_toggled(bool checked)
{
    ui->txtRemoteDB->setEnabled(!checked);
}

void DialogDBServer::on_buttonBox_accepted()
{

}
