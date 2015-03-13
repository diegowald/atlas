#include "dlglocalips.h"
#include "ui_dlglocalips.h"
#include <QtNetwork/QNetworkInterface>
#include <QDebug>

DlgLocalIPs::DlgLocalIPs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLocalIPs)
{
    ui->setupUi(this);
    QNetworkInterface *interface = new QNetworkInterface();
    QList<QHostAddress> list;
    list = interface->allAddresses();
    ui->listWidget->clear();
    foreach (QHostAddress addr, list)
    {
        if (addr.protocol() == QAbstractSocket::IPv4Protocol && !addr.isLoopback())
        {
            qDebug() << addr.toString();
            ui->listWidget->addItem(addr.toString());
        }
    }

}

DlgLocalIPs::~DlgLocalIPs()
{
    delete ui;
}
