#ifndef ALARMA_H
#define ALARMA_H

#include <QObject>
#include "../db/serializable.h"
#include "forward.h"
#include <QDate>

class Alarma : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Alarma(HistoriaClinicaPtr historia, QObject *parent = 0);
    Alarma(mongo::BSONObj &obj, QObject *parent = 0);
    virtual ~Alarma();

    HistoriaClinicaPtr historiaClinica() const;
    QString nota() const;
    QDate fechaCreacion() const;
    QDate fechaAlarma() const;
    bool realizado() const;

    virtual mongo::BSONObj toBson();

    void setNota(const QString &value);
    void setFechaCreacion(const QDate &value);
    void setFechaAlarma(const QDate &value);
    mongo::OID id();
    QString idString();
    void setRealizado(bool value);

signals:

public slots:

private:
    HistoriaClinicaPtr _historiaClinica;
    mongo::OID _idHistoria;
    mongo::OID _id;
    QString _nota;
    QDate _fechaCreacion;
    QDate _fechaAlarma;
    bool _realizado;

};

#endif // ALARMA_H
