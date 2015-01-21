#include "widgetpaciente.h"
#include "ui_widgetpaciente.h"

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
