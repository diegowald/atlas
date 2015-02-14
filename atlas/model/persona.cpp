#include "persona.h"

Persona::Persona(QObject *parent) : QObject(parent)
{
}

Persona::~Persona()
{
}

void Persona::setNombre(const QString &Nombre)
{
    _nombre = Nombre;
}

void Persona::setDomicilio(const QString &Domicilio)
{
    _domicilio = Domicilio;
}

void Persona::setDNI(const QString &DNI)
{
    _dni = DNI;
}

void Persona::setLocalidad(const QString &Localidad)
{
    _localidad = Localidad;
}

void Persona::setTelefonos(const QString &Telefonos)
{
    _telefonos = Telefonos;
}

void Persona::setEmail(const QString &Email)
{
    _email = Email;
}

void Persona::setFechaNacimiento(const QDate &FechaNacimiento)
{
    _fechaNacimiento = FechaNacimiento;
}

void Persona::setEdad(int Edad)
{
    _edad = Edad;
}

void Persona::setOcupacion(const QString &Ocupacion)
{
    _ocupacion = Ocupacion;
}

void Persona::setComoSeEntero(const QString &value)
{
    _comoSeEntero = value;
}

void Persona::setNotas(const QString &notas)
{
    _notas = notas;
}

QString Persona::nombre() const
{
    return _nombre;
}

QString Persona::domicilio() const
{
    return _domicilio;
}

QString Persona::dni() const
{
    return _dni;
}

QString Persona::localidad() const
{
    return _localidad;
}

QString Persona::telefonos() const
{
    return _telefonos;
}

QString Persona::email() const
{
    return _email;
}

QDate Persona::fechaNacimiento() const
{
    return _fechaNacimiento;
}

int Persona::edad() const
{
    return _edad;
}

QString Persona::ocupacion() const
{
    return _ocupacion;
}

QString Persona::comoSeEntero() const
{
    return _comoSeEntero;
}

QString Persona::notas() const
{
    return _notas;
}

mongo::BSONObj Persona::toBson()
{
    mongo::BSONObj obj = BSON(
                "nombre" << _nombre.toStdString()
                << "domicilio" << _domicilio.toStdString()
                << "dni" << _dni.toStdString()
                << "localidad" << _localidad.toStdString()
                << "telefonos" << _telefonos.toStdString()
                << "email" << _email.toStdString()
                << "fechaNacimiento" << _fechaNacimiento.toString().toStdString()
                << "edad" << _edad
                << "ocupacion" << _ocupacion.toStdString()
                << "comoSeEntero" << _comoSeEntero.toStdString()
                << "notas" << _notas.toStdString());
    return obj;
}
