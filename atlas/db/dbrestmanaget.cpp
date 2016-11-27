#include "dbrestmanaget.h"
#include <QDebug>
#include "model/alarma.h"
#include "model/historiaclinica.h"
#include <QMessageBox>
#include <QApplication>

#include "blockinghttp.h"
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QDate>


DBRestManager *DBRestManager::_instance = NULL;

DBRestManager::DBRestManager(QObject *parent) : QObject(parent)
{
    _factory = new Factory();
    _apiKey = "3oUpZRiqZ_CiqIHFvv8YgwU5lfBMCCZg";
    _baseURL = "https://api.mlab.com/api/1";
    _databaseName = "atlasdev";
}

DBRestManager::~DBRestManager()
{
    delete _factory;
}

DBRestManager *DBRestManager::instance()
{
    if (_instance == NULL)
    {
        _instance = new DBRestManager();
    }
    return _instance;
}

QString DBRestManager::connectionString() const
{
    return _connection;
}

/*void DBRestManager::connectToDatabase(mongo::DBClientConnection &conn)
{
    std::string s = "";
    if (conn.connect(connectionString().toStdString(), s))
    {
        qDebug() << s.c_str();

        if (_user.length() > 0)
        {
            conn.auth(_databaseName.toStdString(), _user.toStdString(), _password.toStdString(), s, true );
            qDebug() << s.c_str();
        }
    }
}*/

/*void DBRestManager::setDB(const QString &server, const QString &databaseName, const QString &user, const QString &password)
{
    _server = server;
    _connection = _server;
    _databaseName = databaseName;
    _user = user;
    _password = password;
}*/

void DBRestManager::getAlarmaPaciente(const QString &historiaID)
{
    QString url;
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "alarmas" + "?q={\"idHistoria\": " + historiaID + "}&apiKey=" + _apiKey;

    HttpRequestInput req(url, "GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_getAlarmaPaciente_finished);

    worker->execute(&req);
}

void DBRestManager::on_getAlarmaPaciente_finished(HttpRequestWorker *worker)
{
    QString msg;
    bool error = false;
    if (worker->error_type == QNetworkReply::NoError)
    {
        // communication was successful
        msg = worker->response;
    }
    else
    {
        // an error occurred
        msg = worker->error_str;
        error = true;
    }

    qDebug() << msg;
    AlarmaPtr alarma;

    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(worker->response);
        QJsonObject obj = doc.object();
        alarma = Factory::crearAlarma(obj);
    }
    emit alarmaReturned(alarma);
}

void DBRestManager::getHistoria(const QString & historiaID)
{
    QString url;
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?q={\"_id\": " + historiaID + "}&apiKey=" + _apiKey;

    HttpRequestInput req(url, "GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_getAlarmaPaciente_finished);

    worker->execute(&req);
}


void DBRestManager::on_getHistoria_finished(HttpRequestWorker *worker)
{
    QString msg;
    bool error = false;
    if (worker->error_type == QNetworkReply::NoError)
    {
        // communication was successful
        msg = worker->response;
    }
    else
    {
        // an error occurred
        msg = worker->error_str;
        error = true;
    }

    qDebug() << msg;
    HistoriaClinicaPtr historia;

    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(worker->response);
        QJsonObject obj = doc.object();
        historia = _factory->crearHistoria(obj);
    }

    emit historiaReturned(historia);
}



void DBRestManager::alarmas()
{
    QString url;
    QString q = "{ $and : [ {realizado : false}, {fechaAlarma : { $lte : NumberLong(%1)} } ] }";
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "alarmas" + "?" + q + "&apiKey=" + _apiKey;
    url = url.arg(QDate::currentDate().toJulianDay());


    HttpRequestInput req(url, "GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_alarmas_finished);

    worker->execute(&req);
}

void DBRestManager::on_alarmas_finished(HttpRequestWorker *worker)
{
    QString msg;
    bool error = false;
    if (worker->error_type == QNetworkReply::NoError)
    {
        // communication was successful
        msg = worker->response;
    }
    else
    {
        // an error occurred
        msg = worker->error_str;
        error = true;
    }

    qDebug() << msg;

    QMap<QString, AlarmaPtr> alarmas;

    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(worker->response);
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.count(); ++i)
        {
            QJsonObject obj = arr[i].toObject();
            AlarmaPtr alarma = _factory->crearAlarma(obj);
            if (!alarma->realizado())
                alarmas[alarma->id()] = alarma;
        }
    }

    emit alarmasReturned(alarmas);
}


void DBRestManager::insertHistoria(HistoriaClinicaPtr historia)
{
    QString url;
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?apiKey=" + _apiKey;
    /*
    POST /databases/{database}/collections/{collection}
    Content-Type: application/json
    Body: <JSON data>
*/
    HttpRequestInput req(url, "POST");

    QJsonDocument doc;
    doc.setObject(historia->toJson());
    req.addJsonContent(doc.toJson());

    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_insertHistoria_finished);

    worker->execute(&req);
}

void DBRestManager::on_insertHistoria_finished(HttpRequestWorker *worker)
{
    QString msg;
    bool error = false;
    if (worker->error_type == QNetworkReply::NoError)
    {
        // communication was successful
        msg = worker->response;
    }
    else
    {
        // an error occurred
        msg = worker->error_str;
        error = true;
    }

    qDebug() << msg;
}


void DBRestManager::updateHistoria(HistoriaClinicaPtr historia)
{/*
    mongo::DBClientConnection c;
    connectToDatabase(c);
    std::string s = "";


    QString collection = _databaseName + ".historias";
    c.update(collection.toStdString(),
             BSON("_id" << historia->id()),
             historia->toBson());
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Actualizar historia de paciente", QString::fromStdString(errObj.toString().c_str()));
    }*/
}

void DBRestManager::on_updateHistoria_finished(HttpRequestWorker *worker)
{}

void DBRestManager::insertAlarma(AlarmaPtr alarma)
{/*
    mongo::DBClientConnection c;
    connectToDatabase(c);
    std::string s = "";

    QString collection = _databaseName + ".alarmas";
    c.insert(collection.toStdString(),
             alarma->toBson());
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Crear alarma de paciente", QString::fromStdString(errObj.toString().c_str()));
    }*/
}

void DBRestManager::on_insertAlarma_finished(HttpRequestWorker *worker)
{}

void DBRestManager::updateAlarma(AlarmaPtr alarma)
{/*
    mongo::DBClientConnection c;
    connectToDatabase(c);
    std::string s = "";

    QString collection = _databaseName + ".alarmas";
    c.update(collection.toStdString(),
             BSON("_id" << alarma->id()),
             alarma->toBson(), true);
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Actualizar alarma de paciente", QString::fromStdString(errObj.toString().c_str()));
    }*/
}

void DBRestManager::on_updateAlarma_finished(HttpRequestWorker *worker)
{}


void DBRestManager::historias(const QString queryString)
{
    QString url;
    //QString q = "{ $and : [ {realizado : false}, {fechaAlarma : { $lte : NumberLong(%1)} } ] }";
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?" + queryString + "&apiKey=" + _apiKey;


    HttpRequestInput req(url, "GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_historias_finished);

    worker->execute(&req);
}


void DBRestManager::on_historias_finished(HttpRequestWorker *worker)
{
    QString msg;
    bool error = false;
    if (worker->error_type == QNetworkReply::NoError)
    {
        // communication was successful
        msg = worker->response;
    }
    else
    {
        // an error occurred
        msg = worker->error_str;
        error = true;
    }

    //qDebug() << msg;

    QMap<QString, HistoriaClinicaPtr> map;

    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(worker->response);
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.count(); ++i)
        {
            QJsonObject obj = arr[i].toObject();
            HistoriaClinicaPtr historia = _factory->crearHistoria(obj);
            map[historia->id()] = historia;
        }
    }

    emit historiasReturned(map);
}


void DBRestManager::error(const QString &operacion, const QString &mensaje)
{
    QString msg = "Se ha producido un error en %1: %2";
    QMessageBox::information(QApplication::activeWindow(), "DB Error", msg.arg(operacion, mensaje));
}


bool DBRestManager::existeDNI(const QString &dni, const QString &personaID)
{/*
    mongo::DBClientConnection c;
    connectToDatabase(c);

    std::string s = "";

    mongo::BSONObj query;
    QString queryString = personaID.isSet() ?
                "{ 'persona.dni' : '%1',  '_id' : {$ne : ObjectId(\"%2\")} }" :
                "{ 'persona.dni' : '%1' }";
    queryString = queryString.arg(dni).arg(QString::fromStdString(personaID.toString()));

    qDebug() << queryString;

    query = mongo::fromjson(queryString.toStdString());
    QString collection = _databaseName + ".historias";
    std::auto_ptr<mongo::DBClientCursor> cursor = c.query(collection.toStdString(), query);
    if (c.getLastError().size() != 0)
    {
        mongo::BSONObj errObj = c.getLastErrorDetailed();
        error("Buscar dni duplicado", QString::fromStdString(errObj.toString().c_str()));
    }
    bool exists = false;
    while(cursor->more())
    {
        exists = true;
        break;
    }
    return exists;
*/
}


void DBRestManager::on_existeDNI_finished(HttpRequestWorker *worker)
{}
