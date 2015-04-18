#include "wdgtwithlabel.h"
#include "ui_wdgtwithlabel.h"

WdgtWithLabel::WdgtWithLabel(bool showNotes, QWidget *parent) :
    CustomTooltipWidget(parent),
    ui(new Ui::WdgtWithLabel)
{
    ui->setupUi(this);
    registerTooltipHandler(this);
    ui->txtNotes->setVisible(showNotes);
}

WdgtWithLabel::~WdgtWithLabel()
{
    delete ui;
}

void WdgtWithLabel::addWidget(const QString &label, QWidget *widget)
{
    ui->formLayout->addRow(label, widget);
}

void WdgtWithLabel::setNotes(const QString &newNote)
{
    ui->txtNotes->setText(newNote);
}

QString WdgtWithLabel::notes() const
{
    return ui->txtNotes->text();
}
