#include "dbmanager.h"
#include <QDebug>
#include "model/alarma.h"
#include "model/historiaclinica.h"
#include <QMessageBox>
#include <QApplication>

dbManager *dbManager::_instance = NULL;

dbManager::dbManager(QObject *parent) : QObject(parent)
{
    _factory = new Factory();
}

dbManager::~dbManager()
{
    delete _factory;
}

dbManager *dbManager::instance()
{
    if (_instance == NULL)
    {
        _instance = new dbManager();
    }
    return _instance;
}

QString dbManager::connectionString() const
{
    //return "ds049661.mongolab.com:49661/atlas -u atlas_dev -p atlas1234"; // --authenticationDatabase atlas";
    return _connection;
}

void dbManager::setDB(const QString &server, const QString &databaseName, const QString &user, const QString &password)
{
    _server = server;
    _connection = _server;
    _databaseName = databaseName;
    _user = user;
    _password = password;
}

AlarmaPtr dbManager::getAlarmaPaciente(mongo::OID historiaID)
{
    mongo::DBClientConnection c;
    std::string s = "";
    if (c.connect(connectionString().toStdString(), s))
    {
        qDebug() << s.c_str();

        std::auto_ptr<mongo::DBClientCursor> cursor = c.query("atlas.alarmas", BSON("idHistoria" << historiaID));
        if (c.getLastError().size() != 0)
        {
            mongo::BSONObj errObj = c.getLastErrorDetailed();
            error("Buscar alarma de paciente", QString::fromStdString(errObj.toString().c_str()));
        }
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
}

HistoriaClinicaPtr dbManager::getHistoria(mongo::OID historiaID)
{
    mongo::DBClientConnection c;
    std::string s = "";
    c.connect(connectionString().toStdString(), s);
    qDebug() << s.c_str();

    std::auto_ptr<mongo::DBClientCursor> cursor = c.query("atlas.historias", BSON("_id" << historiaID));
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Buscar historia de paciente", QString::fromStdString(errObj.toString().c_str()));
    }

    HistoriaClinicaPtr historia;
    historia.clear();
    while(cursor->more())
    {
        mongo::BSONObj obj = cursor->next();
        if (!obj.isEmpty())
        {
            historia = _factory->crearHistoria(obj);
        }
    }
    return historia;
}

QMap<QString, AlarmaPtr> dbManager::alarmas()
{
    QMap<QString, AlarmaPtr> map;
    mongo::DBClientConnection c;
    std::string s = "";
    if (c.connect(connectionString().toStdString(), s))
    {
        qDebug() << s.c_str();


        c.auth("atlas", "atlas_dev", "atlas1234", s, true );
        qDebug() << s.c_str();

        QString q = "{ $and : [ {realizado : false}, {fechaAlarma : { $lte : NumberLong(%1)} } ] }";
        mongo::BSONObj qry = mongo::fromjson(q.arg(QDate::currentDate().toJulianDay()).toStdString());
        std::auto_ptr<mongo::DBClientCursor> cursor = c.query("atlas.alarmas", mongo::BSONObj());
        if (c.getLastError().size() != 0)
        {
            mongo::BSONObj errObj = c.getLastErrorDetailed();
            error("Buscar alarmas", QString::fromStdString(errObj.toString().c_str()));
        }
        while(cursor->more())
        {
            mongo::BSONObj obj = cursor->next();
            if (!obj.isEmpty())
            {
                AlarmaPtr alarma = _factory->crearAlarma(obj);
                if (!alarma->realizado())
                    map[QString(alarma->id().toString().c_str())] = alarma;
            }
        }
    }
    qDebug() << s.c_str();
    return map;
}

void dbManager::insertHistoria(HistoriaClinicaPtr historia)
{
    mongo::DBClientConnection c;
    //c.connect("localhost");
    std::string s = "";
    c.connect(connectionString().toStdString(), s);
    qDebug() << QString(historia->toBson().toString().c_str());
    c.insert("atlas.historias", historia->toBson());
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Crear historia de paciente", QString::fromStdString(errObj.toString().c_str()));
    }
}

void dbManager::updateHistoria(HistoriaClinicaPtr historia)
{
    mongo::DBClientConnection c;
    std::string s = "";
    c.connect(connectionString().toStdString(), s);
    c.update("atlas.historias",
             BSON("_id" << historia->id()),
             historia->toBson());
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Actualizar historia de paciente", QString::fromStdString(errObj.toString().c_str()));
    }
}

void dbManager::insertAlarma(AlarmaPtr alarma)
{
    mongo::DBClientConnection c;
    //c.connect("localhost");
    std::string s = "";

    c.connect(connectionString().toStdString(), s);

    c.insert("atlas.alarmas",
             alarma->toBson());
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Crear alarma de paciente", QString::fromStdString(errObj.toString().c_str()));
    }
}

void dbManager::updateAlarma(AlarmaPtr alarma)
{
    mongo::DBClientConnection c;
    //c.connect("localhost");
    std::string s = "";

    c.connect(connectionString().toStdString(), s);

    c.update("atlas.alarmas",
             BSON("_id" << alarma->id()),
             alarma->toBson(), true);
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Actualizar alarma de paciente", QString::fromStdString(errObj.toString().c_str()));
    }
}

QMap<QString, HistoriaClinicaPtr> dbManager::historias(const QString queryString)
{
    QMap<QString, HistoriaClinicaPtr> map;

    mongo::DBClientConnection c;
    std::string s = "";
    c.connect(connectionString().toStdString(), s);
    qDebug() << s.c_str();

    mongo::BSONObj query;

    query = mongo::fromjson(queryString.toStdString());
    std::auto_ptr<mongo::DBClientCursor> cursor = c.query("atlas.historias", query);
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Buscar historias clinicas", QString::fromStdString(errObj.toString().c_str()));
    }
    while(cursor->more())
    {
        mongo::BSONObj obj = cursor->next();
        if (!obj.isEmpty())
        {
            HistoriaClinicaPtr his = _factory->crearHistoria(obj);
            map[his->idString()] = his;
        }
    }
    return map;
}

void dbManager::error(const QString &operacion, const QString &mensaje)
{
    QString msg = "Se ha producido un error en %1: %2";
    QMessageBox::information(QApplication::activeWindow(), "DB Error", msg.arg(operacion, mensaje));
}


