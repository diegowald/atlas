#include "dbsqllitemanager.h"
#include <QDebug>
#include "model/alarma.h"
#include "model/historiaclinica.h"
#include <QMessageBox>
#include <QApplication>
#include <QDate>

#include <QJsonDocument>
#include <QtSql/QSqlQuery>


DBSqlLiteManager::DBSqlLiteManager(QObject *parent) : IDBManager(parent)
{
    _factory = new Factory();
    _apiKey = "3oUpZRiqZ_CiqIHFvv8YgwU5lfBMCCZg";
    _baseURL = "https://api.mlab.com/api/1";
    _databaseName = "atlasdev";
}


DBSqlLiteManager::~DBSqlLiteManager()
{
    delete _factory;
}

QSqlDatabase DBSqlLiteManager::getDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    return db;
}

QString DBSqlLiteManager::connectionString() const
{
    return _connection;
}


void DBSqlLiteManager::getAlarmaPaciente(const QString &historiaID)
{
    QString SQL;
    SQL = "select doc from alarmas where historiaID = '" + historiaID + "'";

    QSqlDatabase db = getDB();

    QSqlQuery res = db.exec(SQL);

    QString resDoc = "";
    while (res.next())
    {
        resDoc= res.value(0).toString();
    }

    qDebug() << resDoc;
    AlarmaPtr alarma;

    bool error = resDoc.length() == 0;

    if (!error)
    {
        QJsonDocument doc = QJsonDocument::fromJson(resDoc.toLatin1());
        QJsonObject obj = doc.object();
        if (!obj.isEmpty())
        {
            alarma = Factory::crearAlarma(obj);
        }
    }
    emit alarmaReturned(alarma, error);
}

void DBSqlLiteManager::getHistoria(const QString & historiaID)
{
    HistoriaClinicaPtr historia;
    if (historiaID.length() > 0)
    {
        QString SQL;
        SQL = "select doc from historias where historiaID = '" + historiaID + "'";
        QSqlDatabase db = getDB();

        QSqlQuery res = db.exec(SQL);

        QString resDoc = "";
        while (res.next())
        {
            resDoc = res.value(0).toString();
        }

        bool error = resDoc.length() == 0;
        qDebug() << resDoc;


        if (!error)
        {
            QJsonDocument doc = QJsonDocument::fromJson(resDoc.toLatin1());
            QJsonObject obj = doc.object();
            if (!obj.isEmpty())
                historia = _factory->crearHistoria(obj);
        }
        emit historiaReturned(historia, error);
    }
}



void DBSqlLiteManager::alarmas()
{
    QString SQL;
    SQL = "select doc from alarmas where realizado = 0 and fechaAlarma <= %1";
    SQL = SQL.arg(QDate::currentDate().toJulianDay());

    QSqlDatabase db = getDB();

    QSqlQuery res = db.exec(SQL);

    bool error = false;
    QMap<QString, AlarmaPtr> alarmas;
    while (res.next())
    {

        QString resDoc = res.value(0).toString();
        QJsonDocument doc = QJsonDocument::fromJson(resDoc.toLatin1());

        QJsonObject obj = doc.object();
        if (!obj.isEmpty())
        {
            AlarmaPtr alarma = _factory->crearAlarma(obj);
            if (!alarma->realizado())
                alarmas[alarma->id()] = alarma;
        }
    }
    emit alarmasReturned(alarmas, error);
}



void DBSqlLiteManager::insertHistoria(HistoriaClinicaPtr historia)
{
    QString SQL = "insert into historias (historiaID, doc) values ('%1', '%2')";
    QJsonDocument doc;
    doc.setObject(historia->toJson());
    SQL = SQL.arg(historia->idString()).arg(QString(doc.toJson()));

    QSqlDatabase db = getDB();
    db.exec(SQL);

    bool error = false;
    emit historiaInserted(historia, error);
}


void DBSqlLiteManager::updateHistoria(HistoriaClinicaPtr historia)
{
    QString SQL = "UPDATE historias SET doc = '%1' WHERE historiaID = '%2'";
    QJsonDocument doc;
    doc.setObject(historia->toJson());
    SQL = SQL.arg(QString(doc.toJson())).arg(historia->idString());

    QSqlDatabase db = getDB();
    db.exec(SQL);

    bool error = false;
    emit historiaUpdated(historia, error);
}

void DBSqlLiteManager::insertAlarma(AlarmaPtr alarma)
{
    QString SQL = "insert into alarmas (alarmaID, historiaID, doc, realizado, fechaAlarma) VALUES ('%1', '%2', '%3', %4, %5)";
    QJsonDocument doc;
    doc.setObject(alarma->toJson());

    SQL = SQL.arg(alarma->idString()).arg(alarma->historiaClinica()->idString()).arg(QString(doc.toJson())).arg(alarma->realizado()).arg(alarma->fechaAlarma().toJulianDay());

    QSqlDatabase db = getDB();
    db.exec(SQL);

    bool error = false;
    emit alarmaInserted(alarma, error);
}

void DBSqlLiteManager::updateAlarma(AlarmaPtr alarma)
{
    QString SQL = "update alarmas set historiaID = '%1', doc = '%2', realizado = %3, fechaAlarma = %4 where alarmaID = '%5'";
    QJsonDocument doc;
    doc.setObject(alarma->toJson());
    SQL = SQL.arg(alarma->historiaClinica()->idString()).arg(QString(doc.toJson())).arg(alarma->realizado()).arg(alarma->fechaAlarma().toJulianDay()).arg(alarma->idString());

    QSqlDatabase db = getDB();
    db.exec(SQL);

    bool error = false;

    emit alarmaUpdated(alarma, error);
}


void DBSqlLiteManager::historias(const QString queryString)
{
    QString SQL = "SELECT doc from historias WHERE %1";
    SQL = SQL.arg(queryString);

    QSqlDatabase db = getDB();
    QSqlQuery res = db.exec(SQL);

    QMap<QString, HistoriaClinicaPtr> map;

    bool error = false;
    while (res.next())
    {
        QString resDoc = res.value(0).toString();

        QJsonDocument doc = QJsonDocument::fromJson(resDoc.toLatin1());

        QJsonObject obj = doc.object();
        if (!obj.isEmpty())
        {
            HistoriaClinicaPtr historia = _factory->crearHistoria(obj);
            map[historia->id()] = historia;
        }
    }

    emit historiasReturned(map, error);
}

void DBSqlLiteManager::historias(QList<QSharedPointer<queryCondition>> &conditions)
{
    QString where;
    foreach(QSharedPointer<queryCondition> condition, conditions)
    {
        QString cond = condition->fieldName();
        switch(condition->condition())
        {
        case queryCondition::conditionOperator::isNull:
            cond += " IS NULL ";
            break;
        case queryCondition::conditionOperator::isNotNull:
            cond += " IS NOT NULL ";
            break;
        case queryCondition::conditionOperator::equals:
            cond += " = '" + condition->values().at(0) + "'";
            break;
        case queryCondition::conditionOperator::notEquals:
            cond += " <> '" + condition->values().at(0) + "'";
            break;
        case queryCondition::conditionOperator::like:
            cond += " = '%" + condition->values().at(0) + "%'";
            break;
        case queryCondition::conditionOperator::in:
            cond += " in (";
            foreach(QString value, condition->values())
            {
                cond += "'" + value + "'";
            }
            cond += ")";
            break;
        case queryCondition::conditionOperator::notIn:
            cond += " not in (";
            foreach(QString value, condition->values())
            {
                cond += "'" + value + "'";
            }
            cond += ")";
            break;
        case queryCondition::conditionOperator::between:
            cond += " between '" + condition->values().at(0) + "' AND '" + condition->values().at(1) + "'";;
            break;
        case queryCondition::conditionOperator::greaterThan:
            cond += " > '" + condition->values().at(0) + "'";
            break;
        case queryCondition::conditionOperator::greaterOrEqual:
            cond += " >= '" + condition->values().at(0) + "'";
            break;
        case queryCondition::conditionOperator::lessThan:
            cond += " < '" + condition->values().at(0) + "'";
            break;
        case queryCondition::conditionOperator::lessOrEqual:
            cond += " <= '" + condition->values().at(0) + "'";
            break;
        }
        if (where.length() > 0)
        {
            where += " AND ";
        }
        where += cond;
    }
    historias(where);
}

void DBSqlLiteManager::error(const QString &operacion, const QString &mensaje)
{
    QString msg = "Se ha producido un error en %1: %2";
    QMessageBox::information(QApplication::activeWindow(), "DB Error", msg.arg(operacion, mensaje));
}


void DBSqlLiteManager::existeDNI(const QString &dni, const QString &personaID)
{
    QString where = "dni = '%1'";
    if (personaID.length() > 0)
    {
        where += " AND historiaID = '%2'";
    }

    QString SQL = "select doc from historias where " + where;
    SQL = SQL.arg(dni).arg(personaID);

    QSqlDatabase db = getDB();

    QSqlQuery res = db.exec(SQL);

    bool exists = false;
    while (res.next())
    {
        exists = true;
    }

    bool error = false;
    emit existeDNIReturned(dni, personaID, exists, error);
}
