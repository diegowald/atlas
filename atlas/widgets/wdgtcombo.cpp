#include "wdgtcombo.h"
#include "ui_wdgtcombo.h"

WdgtCombo::WdgtCombo(bool showNotes, QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtCombo)
{
    ui->setupUi(this);
    registerTooltipHandler(ui->comboBox);
    registerTooltipHandler(this);
    ui->txtNotes->setVisible(showNotes);
}

WdgtCombo::~WdgtCombo()
{
    delete ui;
}

void WdgtCombo::setLista(QStringList &lista)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(lista);
}

QString WdgtCombo::value()
{
    return ui->comboBox->currentText();
}

void WdgtCombo::setValue(const QString &newValue)
{
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(newValue));
}

void WdgtCombo::setNotes(const QString &newNote)
{
    ui->comboBox->setToolTip(newNote);
    setToolTip(newNote);
    ui->txtNotes->setText(newNote);
}

QString WdgtCombo::notes() const
{
    return toolTip();
}
