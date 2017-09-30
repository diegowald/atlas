#include "alarma.h"
#include "historiaclinica.h"

#ifdef USEMONGO
#include "db/dbmanager.h"
#else
//#include "db/dbrestmanaget.h"
#include "db/dbsingleton.h"
#endif
#include <QUuid>

Alarma::Alarma(HistoriaClinicaPtr historia, QObject *parent) : QObject(parent)
{
    _historiaClinica = historia;
    _idHistoria = historia->id();
    _fechaCreacion = QDate::currentDate();
    _fechaAlarma = QDate::currentDate();
    _realizado = false;
    QUuid uuid = QUuid::createUuid();
    _id = uuid.toString();
}

#ifdef USEMONGO
Alarma::Alarma(mongo::BSONObj &obj, QObject *parent) : QObject(parent)
{
    _idHistoria = obj["idHistoria"].OID();
    _historiaClinica = dbManager::instance()->getHistoria(_idHistoria);
    _nota = obj["nota"].String().c_str();
    _fechaCreacion = QDate::fromJulianDay(obj["fechaCreacion"].Long());
    _fechaAlarma = QDate::fromJulianDay(obj["fechaAlarma"].Long());
    _realizado = obj["realizado"].Bool();
    _id = obj["_id"].OID();
}
#else
Alarma::Alarma(QJsonObject &obj, QObject *parent) : QObject(parent)
{
    _idHistoria = obj["idHistoria"].toObject()["$oid"].toString();
    _nota = obj["nota"].toString();
    _fechaCreacion = QDate::fromJulianDay(obj["fechaCreacion"].toInt());
    _fechaAlarma = QDate::fromJulianDay(obj["fechaAlarma"].toInt());
    _realizado = obj["realizado"].toBool();
    _id = obj["_id"].toObject()["$oid"].toString();
    if (_id.length() == 0)
    {
        _id = obj["id"].toString();
    }
    connect(DBSingleton::instance(), &DBSingleton::historiaReturned,
            this, &Alarma::on_historiaReturned);
    DBSingleton::instance()->getHistoria(_idHistoria);
}
#endif

Alarma::~Alarma()
{

}

HistoriaClinicaPtr Alarma::historiaClinica() const
{
    return _historiaClinica;
}

QString Alarma::nota() const
{
    return _nota;
}

QDate Alarma::fechaCreacion() const
{
    return _fechaCreacion;
}

QDate Alarma::fechaAlarma() const
{
    return _fechaAlarma;
}

#ifdef USEMONGO
mongo::BSONObj Alarma::toBson()
{
    if (!_historiaClinica.isNull())
    {
        _idHistoria = _historiaClinica->id();
    }
    mongo::BSONObj obj = BSON(
                "idHistoria" << _idHistoria
                << "nota" << _nota.toStdString()
                << "fechaCreacion" << _fechaCreacion.toJulianDay()
                << "fechaAlarma" << _fechaAlarma.toJulianDay()
                << "realizado" << _realizado);
    return obj;
}
#else
QJsonObject Alarma::toJson()
{
    if (!_historiaClinica.isNull())
    {
        _idHistoria = _historiaClinica->id();
    }
    QJsonObject obj;

    QJsonObject oid;
    oid["$oid"] = _idHistoria;
    obj["idHistoria"] = oid;
    obj["nota"] = _nota;
    obj["fechaCreacion"] = _fechaCreacion.toJulianDay();
    obj["fechaAlarma"] = _fechaAlarma.toJulianDay();
    obj["realizado"] = _realizado;
    obj["id"] = _id;
    return obj;
}
#endif

void Alarma::setNota(const QString &value)
{
    _nota = value;
}

void Alarma::setFechaCreacion(const QDate &value)
{
    _fechaCreacion = value;
}

void Alarma::setFechaAlarma(const QDate &value)
{
    _fechaAlarma = value;
}

#ifdef USEMONGO
mongo::OID Alarma::id()
{
    return _id;
}
#else
QString Alarma::id()
{
    return _id;
}
#endif

QString Alarma::idString()
{
#ifdef USEMONGO
    return QString::fromStdString(_id.toString());
#else
    return _id;
#endif
}

bool Alarma::realizado() const
{
    return _realizado;
}

void Alarma::setRealizado(bool value)
{
    _realizado = value;
}


#ifndef USEMONGO

void Alarma::on_historiaReturned(HistoriaClinicaPtr historia)
{
    if (!historia.isNull() && (historia->id() == _idHistoria))
    {
        _historiaClinica = historia;
    }
}

#endif
