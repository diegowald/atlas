#include "wdgtcombodoble.h"
#include "ui_wdgtcombodoble.h"

WdgtComboDoble::WdgtComboDoble(bool showNotes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtComboDoble)
{
    ui->setupUi(this);
    ui->txtNotes->setVisible(showNotes);
}

WdgtComboDoble::~WdgtComboDoble()
{
    delete ui;
}

void WdgtComboDoble::setLista1(QStringList &lista)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(lista);
}

void WdgtComboDoble::setLista2(QStringList &lista)
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(lista);
}

QString WdgtComboDoble::value1()
{
    return ui->comboBox->currentText();
}

QString WdgtComboDoble::value2()
{
    return ui->comboBox_2->currentText();
}

void WdgtComboDoble::setValue1(const QString &newValue)
{
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(newValue));
}

void WdgtComboDoble::setValue2(const QString &newValue)
{
    ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(newValue));
}

void WdgtComboDoble::setNotes(const QString &newNote)
{
    ui->txtNotes->setPlainText(newNote);
}

QString WdgtComboDoble::notes() const
{
    return ui->txtNotes->toPlainText();
}
