#include "widgetpregunta.h"
#include "ui_widgetpregunta.h"
#include <QMenu>
#include <QInputDialog>

WidgetPregunta::WidgetPregunta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetPregunta)
{
    ui->setupUi(this);
    _overWidget = NULL;

    connect(ui->comboBox_2, &QComboBox::customContextMenuRequested,
            [=] (const QPoint &pos) { (void) pos; popupMenu(ui->comboBox_2);});
    connect(ui->comboBox_3, &QWidget::customContextMenuRequested,
            [=] (const QPoint &pos) { (void) pos; popupMenu(ui->comboBox_3);});
    connect(ui->comboBox_4, &QComboBox::customContextMenuRequested,
            [=] (const QPoint &pos) { (void) pos; popupMenu(ui->comboBox_4);});
    connect(ui->comboBox_5, &QComboBox::customContextMenuRequested,
            [=] (const QPoint &pos) { (void) pos; popupMenu(ui->comboBox_5);});
    connect(this, &QWidget::customContextMenuRequested,
            [=] (const QPoint &pos) { (void) pos; popupMenu(this);});
}

WidgetPregunta::~WidgetPregunta()
{
    delete ui;
}

void WidgetPregunta::popupMenu(QWidget *widget)
{
    _overWidget = widget;
    QMenu *menu = new QMenu(this);
    QAction *action = new QAction("Nota", this);
    connect(action, &QAction::triggered, this, &WidgetPregunta::on_newNote);
    menu->addAction(action);
    menu->popup(QCursor::pos());
}


void WidgetPregunta::on_newNote(bool checked)
{
    QInputDialog dlg(this);
    dlg.setTextValue(toolTip());
    bool ok = false;
    QString oldTooltip = _overWidget->toolTip();
    QString text = QInputDialog::getText(this, "Nota",
                                         "Nota:", QLineEdit::Normal,
                                         oldTooltip, &ok);
    if (ok)
    {
        _overWidget->setToolTip(text);
    }
}
