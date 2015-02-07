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
