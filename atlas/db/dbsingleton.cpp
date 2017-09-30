#include "dbsingleton.h"
#include "dbrestmanaget.h"
#include "dbsqllitemanager.h"
#include "model/alarma.h"
#include "model/historiaclinica.h"

DBSingleton* DBSingleton::_instance = NULL;

DBSingleton::DBSingleton(QObject *parent) : IDBManager(parent)
{
    _dbManager = new DBSqlLiteManager(this);
    //_dbManager = new DBRestManager(this);
    connect(_dbManager, &IDBManager::alarmaReturned, this, &DBSingleton::on_alarmaReturned, Qt::AutoConnection);
    connect(_dbManager, &IDBManager::historiaReturned, this, &DBSingleton::on_historiaReturned, Qt::AutoConnection);
    connect(_dbManager, &IDBManager::historiasReturned, this, &DBSingleton::on_historiasReturned);
    connect(_dbManager, &IDBManager::alarmasReturned, this, &DBSingleton::on_alarmasReturned);

    connect(_dbManager, &IDBManager::historiaInserted, this, &DBSingleton::on_historiaInserted);
    connect(_dbManager, &IDBManager::historiaUpdated, this, &DBSingleton::on_historiaUpdated);

    connect(_dbManager, &IDBManager::alarmaInserted, this, &DBSingleton::on_alarmaInserted);
    connect(_dbManager, &IDBManager::alarmaUpdated, this, &DBSingleton::on_alarmaUpdated);

    connect(_dbManager, &IDBManager::existeDNIReturned, this, &DBSingleton::on_existeDNIReturned);
}



DBSingleton::~DBSingleton()
{
    _dbManager->deleteLater();
}

DBSingleton* DBSingleton::instance()
{
    if (_instance == NULL)
    {
        _instance = new DBSingleton();
    }
    return _instance;
}

void DBSingleton::setParameters(const QString &ip, const QString &database, const QString & username, const QString &password, const QString &filename)
{
    _dbManager->setParameters(ip, database, username, password, filename);
}

void DBSingleton::getAlarmaPaciente(const QString &historiaID)
{
    _dbManager->getAlarmaPaciente(historiaID);
}

void DBSingleton::getHistoria(const QString &historiaID)
{
    _dbManager->getHistoria(historiaID);
}

void DBSingleton::historias(QList<QSharedPointer<queryCondition> > &conditions)
{
    _dbManager->historias(conditions);
}

void DBSingleton::alarmas()
{
    _dbManager->alarmas();
}

void DBSingleton::insertHistoria(HistoriaClinicaPtr historia)
{
    _dbManager->insertHistoria(historia);
}

void DBSingleton::updateHistoria(HistoriaClinicaPtr historia)
{
    _dbManager->updateHistoria(historia);
}

void DBSingleton::insertAlarma(AlarmaPtr alarma)
{
    _dbManager->insertAlarma(alarma);
}

void DBSingleton::updateAlarma(AlarmaPtr alarma)
{
    _dbManager->updateAlarma(alarma);
}

void DBSingleton::existeDNI(const QString &dni, const QString &personaID)
{
    _dbManager->existeDNI(dni, personaID);
}


void DBSingleton::on_alarmaReturned(AlarmaPtr alarma, bool error)
{
    emit alarmaReturned(alarma, error);
}

void DBSingleton::on_historiaReturned(HistoriaClinicaPtr historia, bool error)
{
    emit historiaReturned(historia, error);
}

void DBSingleton::on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias, bool error)
{
    emit historiasReturned(historias, error);
}

void DBSingleton::on_alarmasReturned(QMap<QString, AlarmaPtr> alarmas, bool error)
{
    emit alarmasReturned(alarmas, error);
}

void DBSingleton::on_historiaInserted(HistoriaClinicaPtr historia, bool error)
{
    emit historiaInserted(historia, error);
}

void DBSingleton::on_historiaUpdated(HistoriaClinicaPtr historia, bool error)
{
    emit historiaUpdated(historia, error);
}

void DBSingleton::on_alarmaInserted(AlarmaPtr alarma, bool error)
{
    emit alarmaInserted(alarma, error);
}

void DBSingleton::on_alarmaUpdated(AlarmaPtr alarma, bool error)
{
    emit alarmaUpdated(alarma, error);
}

void DBSingleton::on_existeDNIReturned(const QString &dni, const QString &personaID, bool exists, bool error)
{
    emit existeDNIReturned(dni, personaID, exists, error);
}
