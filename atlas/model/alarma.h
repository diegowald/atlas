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
#ifdef USEMONGO
    Alarma(mongo::BSONObj &obj, QObject *parent = 0);
#else
    Alarma(QJsonObject &obj, QObject *parent = 0);
#endif
    virtual ~Alarma();

    HistoriaClinicaPtr historiaClinica() const;
    QString nota() const;
    QDate fechaCreacion() const;
    QDate fechaAlarma() const;
    bool realizado() const;

#ifdef USEMONGO
    virtual mongo::BSONObj toBson();
#else
    virtual QJsonObject toJson();
#endif

    void setNota(const QString &value);
    void setFechaCreacion(const QDate &value);
    void setFechaAlarma(const QDate &value);
#ifdef USEMONGO
    mongo::OID id();
#else
    QString id();
#endif
    QString idString();
    void setRealizado(bool value);

signals:

public slots:

#ifndef USEMONGO
private slots:
    void on_historiaReturned(HistoriaClinicaPtr historia);
#endif

private:
    HistoriaClinicaPtr _historiaClinica;
#ifdef USEMONGO
    mongo::OID _idHistoria;
    mongo::OID _id;
#else
    QString _idHistoria;
    QString _id;
#endif
    QString _nota;
    QDate _fechaCreacion;
    QDate _fechaAlarma;
    bool _realizado;

};

#endif // ALARMA_H
