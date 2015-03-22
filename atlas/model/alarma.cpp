#include "alarma.h"
#include "historiaclinica.h"
#include "db/dbmanager.h"

Alarma::Alarma(HistoriaClinicaPtr historia, QObject *parent) : QObject(parent)
{
    _historiaClinica = historia;
    _idHistoria = historia->id();
    _fechaCreacion = QDate::currentDate();
    _fechaAlarma = QDate::currentDate();
}

Alarma::Alarma(mongo::BSONObj &obj, QObject *parent) : QObject(parent)
{
    _idHistoria = obj["idHistoria"].OID();
    _historiaClinica = dbManager::instance()->getHistoria(_idHistoria);
    _nota = obj["nota"].String().c_str();
    _fechaCreacion = QDate::fromJulianDay(obj["fechaCreacion"].Int());
    _fechaAlarma = QDate::fromJulianDay(obj["fechaAlarma"].Int());
}

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
                << "fechaAlarma" << _fechaAlarma.toJulianDay());
    return obj;
}

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

mongo::OID Alarma::id()
{
    return _id;
}

QString Alarma::idString()
{
    return QString::fromStdString(_id.toString());
}
