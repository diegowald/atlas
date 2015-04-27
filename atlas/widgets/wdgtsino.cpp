#include "wdgtsino.h"
#include "ui_wdgtsino.h"

WdgtSiNo::WdgtSiNo(bool showNotes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtSiNo)
{
    ui->setupUi(this);
    ui->txtNotes->setVisible(showNotes);
}

WdgtSiNo::~WdgtSiNo()
{
    delete ui;
}

bool WdgtSiNo::value()
{
    return ui->radioSi->isChecked();
}

void WdgtSiNo::setValue(bool newValue)
{
    ui->radioSi->setChecked(newValue);
    ui->radioNo->setChecked(!newValue);
}

void WdgtSiNo::setNotes(const QString &newNote)
{
    ui->txtNotes->setPlainText(newNote);
}

QString WdgtSiNo::notes() const
{
    return ui->txtNotes->toPlainText();
}
