#include "widgetpaciente.h"
#include "ui_widgetpaciente.h"

#include "model/persona.h"
#include <QDebug>
#include "../db/dbmanager.h"

WidgetPaciente::WidgetPaciente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetPaciente)
{
    ui->setupUi(this);
    _dniUnico = true;
    _resaltador = new ResaltadorTexto(ui->txtNotas->document());
}

WidgetPaciente::~WidgetPaciente()
{
    delete ui;
}

void WidgetPaciente::setData(PersonaPtr persona, mongo::OID idHistoria)
{
    ui->txtNombre->setText(persona->nombre());
    ui->txtDocumento->setText(persona->dni());
    ui->txtDomicilio->setText(persona->domicilio());
    ui->txtLocalidad->setText(persona->localidad());
    ui->txtTelefono->setText(persona->telefonos());
    ui->txtEmail->setText(persona->email());
    ui->txtOcupacion->setText(persona->ocupacion());
    ui->txtComoSeEntero->setText(persona->comoSeEntero());
    ui->txtNotas->setText(persona->notas());
    ui->dateFechaNacimiento->setDate(persona->fechaNacimiento());
    ui->spinEdad->setValue(persona->edad());
    _persona = persona;
    _idHistoria = idHistoria;
}

void WidgetPaciente::applyData()
{
    _persona->setNombre(ui->txtNombre->text());
    _persona->setDNI(ui->txtDocumento->text());
    _persona->setDomicilio(ui->txtDomicilio->text());
    _persona->setLocalidad(ui->txtLocalidad->text());
    _persona->setTelefonos(ui->txtTelefono->text());
    _persona->setEmail(ui->txtEmail->text());
    _persona->setOcupacion(ui->txtOcupacion->text());
    _persona->setComoSeEntero(ui->txtComoSeEntero->text());
    _persona->setNotas(ui->txtNotas->toHtml());
    _persona->setEdad(ui->spinEdad->value());
    _persona->setFechaNacimiento(ui->dateFechaNacimiento->date());
}

void WidgetPaciente::on_dateFechaNacimiento_userDateChanged(const QDate &date)
{
    QDate currentDate = QDate::currentDate();
    int age = (date.month() > currentDate.month()) ?
                currentDate.year() - date.year() - 1 :
                currentDate.year() - date.year();
    ui->spinEdad->setValue(age);
    qDebug() << date.toString();
    qDebug() << age;
}

void WidgetPaciente::on_txtDocumento_editingFinished()
{
    // ACA hay que validar que el documento es unico.

    _dniUnico = (0 < ui->txtDocumento->text().length()) &&
            !dbManager::instance()->existeDNI(ui->txtDocumento->text(), _idHistoria);
    if (!_dniUnico)
    {
        ui->txtDocumento->setFocus();
    }
}

bool WidgetPaciente::esDNIUnico()
{
    on_txtDocumento_editingFinished();
    return _dniUnico;
}
