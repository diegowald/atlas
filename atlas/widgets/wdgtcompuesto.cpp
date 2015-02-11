#include "wdgtcompuesto.h"
#include "ui_wdgtcompuesto.h"
#include "../model/preguntabase.h"

WdgtCompuesto::WdgtCompuesto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtCompuesto)
{
    ui->setupUi(this);
}

WdgtCompuesto::~WdgtCompuesto()
{
    delete ui;
}

void WdgtCompuesto::addPregunta(PreguntaBasePtr pregunta)
{
    ui->formLayout->addRow(pregunta->label(), pregunta->widget());
}

void WdgtCompuesto::setLabel(const QString &label)
{
    ui->groupBox->setTitle(label);
}
