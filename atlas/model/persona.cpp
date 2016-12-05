#include "persona.h"

Persona::Persona(QObject *parent) : QObject(parent)
{
}

#ifdef USEMONGO
Persona::Persona(mongo::BSONObj &persona, QObject *parent)
{
    _nombre = persona["nombre"].String().c_str();
    _domicilio = persona["domicilio"].String().c_str();
    _dni = persona["dni"].String().c_str();
    _localidad = persona["localidad"].String().c_str();
    _telefonos = persona["telefonos"].String().c_str();
    _email = persona["email"].String().c_str();


    mongo::BSONType t = persona["fechaNacimiento"].type();

    switch (t)
    {
    case mongo::NumberInt:
        _fechaNacimiento = QDate::fromJulianDay((long) persona["fechaNacimiento"].Int());
        break;
    case mongo::NumberDouble:
        _fechaNacimiento = QDate::fromJulianDay((long) persona["fechaNacimiento"].Double());
        break;
    case mongo::NumberLong:
        _fechaNacimiento = QDate::fromJulianDay(persona["fechaNacimiento"].Long());
        break;
    default:
        break;
    }
    _edad = persona["edad"].type() == mongo::NumberDouble ?
                (int) persona["edad"].Double()
            : persona["edad"].Int();

    _ocupacion = persona["ocupacion"].String().c_str();
    _comoSeEntero = persona["comoSeEntero"].String().c_str();
    _notas = persona["notas"].String().c_str();
}
#else
Persona::Persona(QJsonObject &persona, QObject *parent)
{
    _nombre = persona["nombre"].toString();
    _domicilio = persona["domicilio"].toString();
    _dni = persona["dni"].toString();
    _localidad = persona["localidad"].toString();
    _telefonos = persona["telefonos"].toString();
    _email = persona["email"].toString();


    /*
    mongo::BSONType t = persona["fechaNacimiento"].type();

    switch (t)
    {
    case mongo::NumberInt:
        _fechaNacimiento = QDate::fromJulianDay((long) persona["fechaNacimiento"].Int());
        break;
    case mongo::NumberDouble:
        _fechaNacimiento = QDate::fromJulianDay((long) persona["fechaNacimiento"].Double());
        break;
    case mongo::NumberLong:
        _fechaNacimiento = QDate::fromJulianDay(persona["fechaNacimiento"].Long());
        break;
    default:
        break;
    }
    */

    _fechaNacimiento = QDate::fromJulianDay(persona["fechaNacimiento"].toInt());
    _edad = persona["edad"].toInt();

    _ocupacion = persona["ocupacion"].toString();
    _comoSeEntero = persona["comoSeEntero"].toString();
    _notas = persona["notas"].toString();
}
#endif

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

#ifdef USEMONGO
mongo::BSONObj Persona::toBson()
{
    mongo::BSONObj obj = BSON(
                "nombre" << _nombre.toStdString()
                << "domicilio" << _domicilio.toStdString()
                << "dni" << _dni.toStdString()
                << "localidad" << _localidad.toStdString()
                << "telefonos" << _telefonos.toStdString()
                << "email" << _email.toStdString()
                << "fechaNacimiento" << (long long) _fechaNacimiento.toJulianDay()
                << "edad" << _edad
                << "ocupacion" << _ocupacion.toStdString()
                << "comoSeEntero" << _comoSeEntero.toStdString()
                << "notas" << _notas.toStdString());
    return obj;
}
#else
QJsonObject Persona::toJson()
{
    QJsonObject obj;
    obj["nombre"] = _nombre;
    obj["domicilio"] = _domicilio;
    obj["dni"] = _dni;
    obj["localidad"] = _localidad;
    obj["telefonos"] = _telefonos;
    obj["email"] = _email;
    obj["fechaNacimiento"] = _fechaNacimiento.toJulianDay();
    obj["edad"] = _edad;
    obj["ocupacion"] = _ocupacion;
    obj["comoSeEntero"] = _comoSeEntero;
    obj["notas"] = _notas;
    return obj;
}
#endif

QString Persona::toHtml()
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";

    s += "<tr>";
    s += QString("<td>Nombre: %1</td><td>DNI: %2</td>").arg(_nombre).arg(_dni);
    s += "</tr><tr>";
    s += QString("<td>Domicilio: %1</td><td>Localidad: %2</td>").arg(_domicilio).arg(_localidad);
    s += "</tr><tr>";
    s += QString("<td>Telefonos: %1</td><td>email: %2</td>").arg(_telefonos).arg(_email);
    s += "</tr><tr>";
    s += QString("<td>Fecha de Nacimiento: %1</td><td>Edad: %2</td>").arg(_fechaNacimiento.toString("dd/MM/yyyy")).arg(_edad);
    s += "</tr><tr>";
    s += QString("<td>Ocupacion: %1</td><td>Como se entero: %2</td>").arg(_ocupacion).arg(_comoSeEntero);
    s += "</tr><tr>";
    s += QString("<td colspan=\"2\">Notas: %1</td><td>DNI: %2</td>").arg(_notas);
    s += "</tr>";
    s += "</table>";
    return s;
}
