#ifndef PERSONA_H
#define PERSONA_H

#include <QObject>
#include <QDate>

class Persona : public QObject
{
    Q_OBJECT
public:
    explicit Persona(QObject *parent = 0);
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

    QString nombre() const;
    QString domicilio() const;
    QString dni() const;
    QString localidad() const;
    QString telefonos() const;
    QString email() const;
    QDate fechaNacimiento() const;
    int edad() const;
    QString ocupacion() const;

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
};

#endif // PERSONA_H
