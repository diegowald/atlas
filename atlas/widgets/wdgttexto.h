#ifndef WDGTTEXTO_H
#define WDGTTEXTO_H

#include "customtooltipwidget.h"

namespace Ui {
class WdgtTexto;
}

class WdgtTexto : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtTexto(QWidget *parent = 0);
    ~WdgtTexto();

    QString value();
    void setValue(const QString &value);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtTexto *ui;
};

#endif // WDGTTEXTO_H
