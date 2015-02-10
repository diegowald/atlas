#ifndef WIDGETPACIENTE_H
#define WIDGETPACIENTE_H

#include <QWidget>
#include "model/forward.h"

namespace Ui {
class WidgetPaciente;
}

class WidgetPaciente : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPaciente(QWidget *parent = 0);
    ~WidgetPaciente();
    void setData(PersonaPtr persona);

private:
    Ui::WidgetPaciente *ui;
};

#endif // WIDGETPACIENTE_H
