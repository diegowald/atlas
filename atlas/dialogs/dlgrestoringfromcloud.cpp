#include "dlgrestoringfromcloud.h"
#include "ui_dlgrestoringfromcloud.h"

#include "db/dbsingleton.h"
#include <model/historiaclinica.h>
#include <model/alarma.h>
#include <QSharedPointer>
#include <QMap>
#include <QTimer>


DlgRestoringFromCloud::DlgRestoringFromCloud(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgRestoringFromCloud)
{
    ui->setupUi(this);

    ui->lblInformacion->setVisible(false);
    ui->pBarPorcentaje->setVisible(false);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowTitleHint);

    connect(&_cloud, &DBRestManager::historiasReturned,  this, &DlgRestoringFromCloud::on_historiasReturned);
    connect(&_cloud, &DBRestManager::alarmasReturned, this, &DlgRestoringFromCloud::on_alarmasReturned);

    QTimer::singleShot(500, this, &DlgRestoringFromCloud::startProcess);
}

DlgRestoringFromCloud::~DlgRestoringFromCloud()
{
    delete ui;
}


void DlgRestoringFromCloud::startProcess()
{
    ui->lblInformacion->setText("Obteniendo Historias clinicas desde la nube...");
    ui->lblInformacion->setVisible(true);
    QList<QSharedPointer<queryCondition> > conditions;
    _cloud.historias(conditions);
}

void DlgRestoringFromCloud::on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias, bool error)
{
    ui->pBarPorcentaje->setMinimum(0);
    ui->pBarPorcentaje->setMaximum(historias.count() - 1);
    ui->pBarPorcentaje->setVisible(true);
    ui->lblInformacion->setText("Importando historias clinicas...");
    int i = 0;
    foreach(QString idHistoria, historias.keys())
    {
        ui->pBarPorcentaje->setValue(i);
        QApplication::processEvents();
        qDebug() << idHistoria;
        DBSingleton::instance()->insertHistoria(historias[idHistoria]);
        ++i;
    }
    ui->lblInformacion->setText("Obteniendo Historias clinicas desde la nube...");
    QApplication::processEvents();
    _cloud.alarmas();
}

void DlgRestoringFromCloud::on_alarmasReturned(QMap<QString, AlarmaPtr> alarmas, bool error)
{
    ui->pBarPorcentaje->setMinimum(0);
    ui->pBarPorcentaje->setMaximum(alarmas.count() - 1);
    ui->pBarPorcentaje->setVisible(true);
    ui->lblInformacion->setText("Importando alarmas...");
    int i = 0;
    foreach(QString alarmaID, alarmas.keys())
    {
        ui->pBarPorcentaje->setValue(i);
        QApplication::processEvents();
        qDebug() << alarmaID;
        DBSingleton::instance()->insertAlarma(alarmas[alarmaID]);
        ++i;
    }
    this->close();
}
