#ifndef WDGTCOMBO_H
#define WDGTCOMBO_H

#include "customtooltipwidget.h"
#include <QStringList>

namespace Ui {
class WdgtCombo;
}

class WdgtCombo : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtCombo(bool showNotes, QWidget *parent = 0);
    ~WdgtCombo();

    void setLista(QStringList &lista);
    QString value();
    void setValue(const QString &newValue);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtCombo *ui;
};

#endif // WDGTCOMBO_H
