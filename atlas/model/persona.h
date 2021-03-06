#ifndef PERSONA_H
#define PERSONA_H

#include <QObject>
#include <QDate>
#include "../db/serializable.h"
#include "htmlable.h"

class Persona : public QObject, public Serializable, public htmlAble
{
    Q_OBJECT
public:
    explicit Persona(QObject *parent = 0);
#ifdef USEMONGO
    Persona(mongo::BSONObj &persona, QObject *parent = 0);
#else
    Persona(QJsonObject &persona, QObject *parent = 0);
#endif
    ~Persona();

    void setNombre(const QString &Nombre);
    void setDomicilio(const QString &Domicilio);
    void setDNI(const QString &DNI);
    void setLocalidad(const QString &Localidad);
    void setTelefonos(const QString &Telefonos);
    void setEmail(const QString &Email);
    void setFechaNacimiento(const QDate &FechaNacimiento);
    void setEdad(int Edad);
    void setOcupacion(const QString &Ocupacion);
    void setComoSeEntero(const QString &value);
    void setNotas(const QString &notas);

    QString nombre() const;
    QString domicilio() const;
    QString dni() const;
    QString localidad() const;
    QString telefonos() const;
    QString email() const;
    QDate fechaNacimiento() const;
    int edad() const;
    QString ocupacion() const;
    QString comoSeEntero() const;
    QString notas() const;

#ifdef USEMONGO
    virtual mongo::BSONObj toBson();
#else
    virtual QJsonObject toJson();
#endif

    virtual QString toHtml();

signals:

public slots:

private:
    QString _nombre;
    QString _domicilio;
    QString _dni;
    QString _localidad;
    QString _telefonos;
    QString _email;
    QDate _fechaNacimiento;
    int _edad;
    QString _ocupacion;
    QString _comoSeEntero;
    QString _notas;
#ifdef USEMONGO
    mongo::OID _id;
#else
    QString _id;
#endif
};

#endif // PERSONA_H
