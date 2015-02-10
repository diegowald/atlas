#include "widgetpaciente.h"
#include "ui_widgetpaciente.h"

#include "model/persona.h"

WidgetPaciente::WidgetPaciente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetPaciente)
{
    ui->setupUi(this);
}

WidgetPaciente::~WidgetPaciente()
{
    delete ui;
}

void WidgetPaciente::setData(PersonaPtr persona)
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
}
