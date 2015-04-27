#include "wdgtcombo.h"
#include "ui_wdgtcombo.h"

WdgtCombo::WdgtCombo(bool showNotes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtCombo)
{
    ui->setupUi(this);
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
    ui->txtNotes->setPlainText(newNote);
}

QString WdgtCombo::notes() const
{
    return ui->txtNotes->toPlainText();
}
