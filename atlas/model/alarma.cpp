#include "alarma.h"
#include "historiaclinica.h"
#include "db/dbmanager.h"

Alarma::Alarma(HistoriaClinicaPtr historia, QObject *parent) : QObject(parent)
{
    _historiaClinica = historia;
    _idHistoria = historia->id();
    _fechaCreacion = QDate::currentDate();
    _fechaAlarma = QDate::currentDate();
    _realizado = false;
}

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
                << "fechaAlarma" << _fechaAlarma.toJulianDay()
                << "realizado" << _realizado);
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

bool Alarma::realizado() const
{
    return _realizado;
}

void Alarma::setRealizado(bool value)
{
    _realizado = value;
}
