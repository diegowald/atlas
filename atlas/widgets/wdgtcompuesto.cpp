#include "wdgtcompuesto.h"
#include "ui_wdgtcompuesto.h"
#include "../model/preguntabase.h"

WdgtCompuesto::WdgtCompuesto(bool showNotes, QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtCompuesto)
{
    ui->setupUi(this);
    registerTooltipHandler(ui->groupBox);
    registerTooltipHandler(this);
    ui->groupBox->setChecked(false);
    ui->txtNotes->setVisible(showNotes);
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

void WdgtCompuesto::setChecked(bool checked)
{
    ui->groupBox->setChecked(checked);
}

bool WdgtCompuesto::isChecked() const
{
    return ui->groupBox->isChecked();
}

void WdgtCompuesto::setNotes(const QString &newNote)
{
    ui->groupBox->setToolTip(newNote);
    setToolTip(newNote);
    ui->txtNotes->setText(newNote);
}

QString WdgtCompuesto::notes() const
{
    return toolTip();
}
