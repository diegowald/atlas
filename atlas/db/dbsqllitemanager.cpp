#include "dbsqllitemanager.h"
#include <QDebug>
#include "model/alarma.h"
#include "model/historiaclinica.h"
#include "model/persona.h"
#include <QMessageBox>
#include <QApplication>
#include <QDate>

#include <QJsonDocument>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QVariant>

DBSqlLiteManager::DBSqlLiteManager(QObject *parent) : IDBManager(parent)
{
}


DBSqlLiteManager::~DBSqlLiteManager()
{
    delete _factory;
}

void DBSqlLiteManager::setParameters(const QString &ip, const QString &database, const QString & username, const QString &password, const QString &filename)
{
    Q_UNUSED(ip);
    Q_UNUSED(database);
    Q_UNUSED(username);
    Q_UNUSED(password);
    _filename = filename;
}

QSqlDatabase DBSqlLiteManager::getDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(_filename);
    bool opened = db.open();
    if (!opened)
    {
        QMessageBox::information(NULL, "Open", db.lastError().text());
    }
    return db;
}

QString DBSqlLiteManager::connectionString() const
{
    return _filename;
}


void DBSqlLiteManager::getAlarmaPaciente(const QString &historiaID)
{
    QSqlDatabase db = getDB();

    QString SQL;
    SQL = "select doc from alarmas where historiaID = :historiaID";

    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":historiaID", historiaID);

    query.exec();
    qDebug() << query.lastError().text();

    QString resDoc = "";
    while (query.next())
    {
        resDoc = query.value(0).toString();
        break;
    }

    qDebug() << resDoc;
    AlarmaPtr alarma;

    bool error = false;
    if (resDoc.length() > 0)
    {
        QJsonDocument doc = QJsonDocument::fromJson(resDoc.toLatin1());
        QJsonObject obj = doc.object();
        if (!obj.isEmpty())
        {
            alarma = Factory::crearAlarma(obj);
        }
    }
    emit IDBManager::alarmaReturned(alarma, error);
}

void DBSqlLiteManager::getHistoria(const QString & historiaID)
{
    HistoriaClinicaPtr historia;
    if (historiaID.length() > 0)
    {
        QSqlDatabase db = getDB();

        QString SQL;
        SQL = "select doc from historias where historiaID = :historiaID";

        QSqlQuery query;
        query.prepare(SQL);
        query.bindValue(":historiaID", historiaID);

        query.exec();

        QString resDoc = "";
        while (query.next())
        {
            resDoc = query.value(0).toString();
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
        emit IDBManager::historiaReturned(historia, error);
    }
}



void DBSqlLiteManager::alarmas()
{
    QSqlDatabase db = getDB();
    QString SQL;
    SQL = "select doc from alarmas where realizado = 0 and fechaAlarma <= :fechaAlarma";

    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":fechaAlarma", QDate::currentDate().toJulianDay());

    query.exec();

    bool error = false;
    QMap<QString, AlarmaPtr> alarmas;
    while (query.next())
    {

        QString resDoc = query.value(0).toString();
        QJsonDocument doc = QJsonDocument::fromJson(resDoc.toLatin1());

        QJsonObject obj = doc.object();
        if (!obj.isEmpty())
        {
            AlarmaPtr alarma = _factory->crearAlarma(obj);
            if (!alarma->realizado())
                alarmas[alarma->id()] = alarma;
        }
    }
    emit IDBManager::alarmasReturned(alarmas, error);
}



void DBSqlLiteManager::insertHistoria(HistoriaClinicaPtr historia)
{
    QString SQL = "insert into historias (historiaID, doc, nombre, dni, localidad, fechaSegundaConsulta) values (:historiaID, :doc, :nombre, :dni, :localidad, :fechaSegundaConsulta)";
    QJsonDocument doc;
    doc.setObject(historia->toJson());

    QSqlDatabase db = getDB();
    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":historiaID", historia->idString());
    query.bindValue(":doc", QString(doc.toJson()));
    query.bindValue(":nombre", historia->persona()->nombre());
    query.bindValue(":dni", historia->persona()->dni());
    query.bindValue(":localidad", historia->persona()->localidad());
    query.bindValue(":fechaSegundaConsulta", historia->fechaSegundaConsulta());
    query.exec();

    qDebug() << db.lastError().text();
    bool error = false;
    emit IDBManager::historiaInserted(historia, error);
}


void DBSqlLiteManager::updateHistoria(HistoriaClinicaPtr historia)
{
    QSqlDatabase db = getDB();

    QString SQL = "UPDATE historias SET doc = :doc, nombre = :nombre, dni = :dni, localidad = :localidad, fechaSegundaConsulta = :fechaSegundaConsulta  WHERE historiaID = :historiaID";

    QJsonDocument doc;
    doc.setObject(historia->toJson());

    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":doc", QString(doc.toJson()));
    qDebug() << QString(doc.toJson());
    query.bindValue(":nombre", historia->persona()->nombre());
    query.bindValue(":dni", historia->persona()->dni());
    query.bindValue(":localidad", historia->persona()->localidad());
    query.bindValue(":fechaSegundaConsulta", historia->fechaSegundaConsulta());
    query.bindValue(":historiaID", historia->idString());

    bool error = query.exec();
    qDebug() << db.lastError().databaseText();
    emit IDBManager::historiaUpdated(historia, error);
}

void DBSqlLiteManager::insertAlarma(AlarmaPtr alarma)
{
    QSqlDatabase db = getDB();
    QString SQL = "insert into alarmas (alarmaID, historiaID, doc, realizado, fechaAlarma) VALUES (:alarmaID, :historiaID, :doc, :realizado, :fechaAlarma)";
    QJsonDocument doc;
    doc.setObject(alarma->toJson());

    QSqlQuery query;
    query.prepare(SQL);

    query.bindValue(":alarmaID", alarma->idString());
    query.bindValue(":historiaID", alarma->historiaClinica().isNull() ? "" : alarma->historiaClinica()->idString());
    qDebug() << doc.toJson();
    query.bindValue(":doc", QString(doc.toJson()));
    query.bindValue(":realizado", alarma->realizado() ? 1 : 0);
    query.bindValue(":fechaAlarma", alarma->fechaAlarma().toJulianDay());

    query.exec();
qDebug() << query.lastError().text();
    bool error = false;
    emit IDBManager::alarmaInserted(alarma, error);
}

void DBSqlLiteManager::updateAlarma(AlarmaPtr alarma)
{
    QSqlDatabase db = getDB();


    QString SQL = "update alarmas set historiaID = :historiaID, doc = :doc, realizado = :realizado, fechaAlarma = :fechaALarma where alarmaID = :alarmaID";
    QJsonDocument doc;
    doc.setObject(alarma->toJson());

    QSqlQuery  query;
    query.prepare(SQL);
    query.bindValue(":historiaID", alarma->historiaClinica()->idString());
    query.bindValue(":doc", QString(doc.toJson()));
    query.bindValue(":realizado", alarma->realizado());
    query.bindValue(":fechaALarma", alarma->fechaAlarma().toJulianDay());
    query.bindValue(":alarmaID", alarma->idString());

    bool error = query.exec();

    emit IDBManager::alarmaUpdated(alarma, error);
}


void DBSqlLiteManager::historias(const QString &queryString)
{
    QString SQL = "SELECT doc from historias";
    if (queryString.trimmed().length() > 0)
    {
        SQL = SQL + " WHERE " + queryString;
    }
qDebug() << SQL;
    QSqlDatabase db = getDB();
    QSqlQuery res = db.exec(SQL);
    qDebug() << res.lastError().text();
    QMap<QString, HistoriaClinicaPtr> map;

    bool error = false;
    while (res.next())
    {
        QString resDoc = res.value(0).toString();

        QJsonDocument doc = QJsonDocument::fromJson(resDoc.toUtf8());

        qDebug() << doc.toJson();

        QJsonObject obj = doc.object();
        qDebug() << obj;
        if (!obj.isEmpty())
        {
            HistoriaClinicaPtr historia = _factory->crearHistoria(obj);
            qDebug() << historia->idString();
            map[historia->id()] = historia;
        }
    }

    emit IDBManager::historiasReturned(map, error);
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
    emit IDBManager::existeDNIReturned(dni, personaID, exists, error);
}
