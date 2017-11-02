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


DBRestManager::DBRestManager(QObject *parent) : IDBManager(parent)
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

void DBRestManager::setParameters(const QString &ip, const QString &database, const QString & username, const QString &password, const QString &filename)
{
    Q_UNUSED(ip)
    Q_UNUSED(database);
    Q_UNUSED(username);
    Q_UNUSED(password);
    Q_UNUSED(filename);
}


QString DBRestManager::connectionString() const
{
    return _connection;
}


void DBRestManager::getAlarmaPaciente(const QString &historiaID)
{
    QString url;
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "alarmas" + "?q={\"idHistoria\":{\"$oid\":\"" + historiaID + "\"}}&apiKey=" + _apiKey;

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
        if (!obj.isEmpty())
        {
            alarma = Factory::crearAlarma(obj);
        }
    }
    emit alarmaReturned(alarma, error);
}

void DBRestManager::getHistoria(const QString & historiaID)
{
    if (historiaID.length() > 0)
    {
        QString url;
        QString q = "q={\"id\":{\"$oid\":\"%1\"}}";
        url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?" + q.arg(historiaID) + "&apiKey=" + _apiKey;

        HttpRequestInput req(url, "GET");
        req.var_layout = URL_ENCODED;
        HttpRequestWorker *worker = new HttpRequestWorker(this);
        connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_getHistoria_finished);

        worker->execute(&req);
    }
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
        if (!obj.isEmpty())
            historia = _factory->crearHistoria(obj);
    }

    emit historiaReturned(historia, error);
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
            if (!obj.isEmpty())
            {
                AlarmaPtr alarma = _factory->crearAlarma(obj);
                if (!alarma->realizado())
                    alarmas[alarma->id()] = alarma;
            }
        }
    }

    emit alarmasReturned(alarmas, error);
}


void DBRestManager::insertHistoria(HistoriaClinicaPtr historia)
{
    QString url;
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?apiKey=" + _apiKey;

    HttpRequestInput req(url, "POST");

    QJsonDocument doc;
    doc.setObject(historia->toJson());
    req.addJsonContent(doc.toJson());

    qDebug() << doc.toJson();

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

    HistoriaClinicaPtr historia;
    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(worker->response);
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.count(); ++i)
        {
            QJsonObject obj = arr[i].toObject();
            if (!obj.isEmpty())
            {
                historia = _factory->crearHistoria(obj);
                break;
            }
        }
    }
    emit historiaInserted(historia, error);
}


void DBRestManager::updateHistoria(HistoriaClinicaPtr historia)
{
    QString url;
    QString q = "&q={\"_id\":{\"$oid\":\"%1\"}}";
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?apiKey=" + _apiKey + q.arg(historia->id());

    qDebug() << url;
    HttpRequestInput req(url, "PUT");

    QJsonDocument doc;
    doc.setObject(historia->toJson());
    QString content = "{$set:%1}";
    req.addJsonContent(content.arg(QString(doc.toJson())));

    qDebug() << content.arg(QString(doc.toJson(QJsonDocument::JsonFormat::Compact)));

    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_updateHistoria_finished);

    worker->execute(&req);
}

void DBRestManager::on_updateHistoria_finished(HttpRequestWorker *worker)
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
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.count(); ++i)
        {
            QJsonObject obj = arr[i].toObject();
            if (!obj.isEmpty())
            {
                historia = _factory->crearHistoria(obj);
                break;
            }
        }
    }

    emit historiaUpdated(historia, error);
}

void DBRestManager::insertAlarma(AlarmaPtr alarma)
{
    QString url;
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "alarmas" + "?apiKey=" + _apiKey;

    HttpRequestInput req(url, "POST");

    QJsonDocument doc;
    doc.setObject(alarma->toJson());
    req.addJsonContent(doc.toJson());

    qDebug() << doc.toJson();

    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_insertAlarma_finished);

    worker->execute(&req);
}

void DBRestManager::on_insertAlarma_finished(HttpRequestWorker *worker)
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
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.count(); ++i)
        {
            QJsonObject obj = arr[i].toObject();
            if (!obj.isEmpty())
            {
                alarma = _factory->crearAlarma(obj);
                break;
            }
        }
    }

    emit alarmaInserted(alarma, error);
}

void DBRestManager::updateAlarma(AlarmaPtr alarma)
{
    QString url;
    QString q = "&q={\"_id\":{\"$oid\":\"%1\"}}";
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "alarmas" + "?apiKey=" + _apiKey + q.arg(alarma->id());

    HttpRequestInput req(url, "PUT");

    QJsonDocument doc;
    doc.setObject(alarma->toJson());
    QString content = "{$set:%1}";
    req.addJsonContent(content.arg(QString(doc.toJson())));

    qDebug() << doc.toJson();

    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_updateAlarma_finished);

    worker->execute(&req);
}

void DBRestManager::on_updateAlarma_finished(HttpRequestWorker *worker)
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
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.count(); ++i)
        {
            QJsonObject obj = arr[i].toObject();
            if (!obj.isEmpty())
            {
                alarma = _factory->crearAlarma(obj);
                break;
            }
        }
    }

    emit alarmaUpdated(alarma, error);
}


void DBRestManager::historias(const QString &queryString)
{
    QString url;
    if (queryString.length() > 0)
    {
        url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?q=" + queryString + "&apiKey=" + _apiKey;
    }
    else
    {
        url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?apiKey=" + _apiKey;
    }
    HttpRequestInput req(url, "GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_historias_finished);

    worker->execute(&req);
}

void DBRestManager::historias(QList<QSharedPointer<queryCondition> > &conditions)
{
    QString where = "";
    if (conditions.count() > 0)
    {
        foreach(QSharedPointer<queryCondition> condition, conditions)
        {
            QString cond;
            switch(condition->condition())
            {
            case queryCondition::conditionOperator::isNull:
                break;
            case queryCondition::conditionOperator::isNotNull:
                break;
            case queryCondition::conditionOperator::equals:
                cond = QString("'%1':\"%2\"").arg(condition->fieldName()).arg(condition->values().at(0));
                break;
            case queryCondition::conditionOperator::notEquals:
                break;
            case queryCondition::conditionOperator::like:
                cond = QString("$text : { $search : \"%1\" }").arg(condition->values().at(0));
                break;
            case queryCondition::conditionOperator::in:
                break;
            case queryCondition::conditionOperator::notIn:
                break;
            case queryCondition::conditionOperator::between:
                break;
            case queryCondition::conditionOperator::greaterThan:
                break;
            case queryCondition::conditionOperator::greaterOrEqual:
                break;
            case queryCondition::conditionOperator::lessThan:
                break;
            case queryCondition::conditionOperator::lessOrEqual:
                break;
            }
            if (where.length() > 0)
            {
                where += ", ";
            }
            where += cond;
        }
        where = "{" + where + "}";
    }
    historias(where);
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

    qDebug() << msg;

    QMap<QString, HistoriaClinicaPtr> map;

    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(worker->response);
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.count(); ++i)
        {
            QJsonObject obj = arr[i].toObject();
            if (!obj.isEmpty())
            {
                HistoriaClinicaPtr historia = _factory->crearHistoria(obj);
                map[historia->id()] = historia;
            }
        }
    }

    emit historiasReturned(map, error);
}


void DBRestManager::error(const QString &operacion, const QString &mensaje)
{
    QString msg = "Se ha producido un error en %1: %2";
    QMessageBox::information(QApplication::activeWindow(), "DB Error", msg.arg(operacion, mensaje));
}


void DBRestManager::existeDNI(const QString &dni, const QString &personaID)
{
    QString url;
    QString queryString = personaID.length() > 0 ?
                "q:{'persona.dni':'%1','_id':{$ne:ObjectId(\"%2\")}}" :
                "q:{'persona.dni':'%1'}";
    queryString = queryString.arg(dni).arg(personaID);

    qDebug() << queryString;


    //QString q = "{ $and : [ {realizado : false}, {fechaAlarma : { $lte : NumberLong(%1)} } ] }";
    url = _baseURL + "/databases/" + _databaseName + "/collections/" + "historias" + "?" + queryString + "&apiKey=" + _apiKey;


    HttpRequestInput req(url, "GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, &HttpRequestWorker::on_execution_finished, this, &DBRestManager::on_existeDNI_finished);

    worker->execute(&req);
}

void DBRestManager::on_existeDNI_finished(HttpRequestWorker *worker)
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

    bool exists = false;
    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(worker->response);
        QJsonArray arr = doc.array();
        exists = arr.count() > 0;
    }

    QString dni;
    QString personaID;

    emit existeDNIReturned(dni, personaID, exists, error);
}
