#include "dialoghistoriaclinica.h"
#include "ui_dialoghistoriaclinica.h"

DialogHistoriaClinica::DialogHistoriaClinica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHistoriaClinica)
{
    ui->setupUi(this);
}

DialogHistoriaClinica::~DialogHistoriaClinica()
{
    delete ui;
}
