#ifndef WDGTCOMPUESTO_H
#define WDGTCOMPUESTO_H

#include <QWidget>
#include "../model/forward.h"

namespace Ui {
class WdgtCompuesto;
}

class WdgtCompuesto : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtCompuesto(QWidget *parent = 0);
    ~WdgtCompuesto();

    void setLabel(const QString &label);
    void addPregunta(PreguntaBasePtr pregunta);

private:
    Ui::WdgtCompuesto *ui;
};

#endif // WDGTCOMPUESTO_H
