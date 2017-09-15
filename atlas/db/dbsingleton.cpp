#include "dbsingleton.h"
#include "dbrestmanaget.h"
#include "dbsqllitemanager.h"
#include "model/alarma.h"
#include "model/historiaclinica.h"

QSharedPointer<DBSingleton> DBSingleton::_instance = NULL;

DBSingleton::DBSingleton(QObject *parent) : IDBManager(parent)
{
    //_dbManager = QSharedPointer<IDBManager>(new DBSqlLiteManager(this));
    _dbManager = QSharedPointer<IDBManager>(new DBRestManager(this));
    connect(_dbManager.data(), &IDBManager::alarmaReturned, this, &DBSingleton::alarmaReturned);
    connect(_dbManager.data(), &IDBManager::historiaReturned, this, &DBSingleton::historiaReturned);
    connect(_dbManager.data(), &IDBManager::historiasReturned, this, &DBSingleton::historiasReturned);
    connect(_dbManager.data(), &IDBManager::alarmasReturned, this, &DBSingleton::alarmasReturned);

    connect(_dbManager.data(), &IDBManager::historiaInserted, this, &DBSingleton::historiaInserted);
    connect(_dbManager.data(), &IDBManager::historiaUpdated, this, &DBSingleton::historiaUpdated);

    connect(_dbManager.data(), &IDBManager::alarmaInserted, this, &DBSingleton::alarmaInserted);
    connect(_dbManager.data(), &IDBManager::alarmaUpdated, this, &DBSingleton::alarmaUpdated);

    connect(_dbManager.data(), &IDBManager::existeDNIReturned, this, &DBSingleton::existeDNIReturned);
}



DBSingleton::~DBSingleton()
{
}

QSharedPointer<DBSingleton> DBSingleton::instance()
{
    if (_instance == NULL)
    {
        _instance = QSharedPointer<DBSingleton>(new DBSingleton());
    }
    return _instance;
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
