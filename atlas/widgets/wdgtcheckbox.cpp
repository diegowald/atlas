#include "wdgtcheckbox.h"
#include "ui_wdgtcheckbox.h"

WdgtCheckBox::WdgtCheckBox(bool showNotes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdgtCheckBox)
{
    ui->setupUi(this);
    ui->txtNotes->setVisible(showNotes);
}

WdgtCheckBox::~WdgtCheckBox()
{
    delete ui;
}

bool WdgtCheckBox::value()
{
    return ui->check->isChecked();
}

void WdgtCheckBox::setValue(bool newValue)
{
    ui->check->setChecked(newValue);
}

void WdgtCheckBox::setNotes(const QString &newNote)
{
    ui->txtNotes->setText(newNote);
}

QString WdgtCheckBox::notes() const
{
    return ui->txtNotes->text();
}
