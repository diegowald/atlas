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
    void applyData();

private slots:
    void on_dateFechaNacimiento_userDateChanged(const QDate &date);

private:
    Ui::WidgetPaciente *ui;
    PersonaPtr _persona;
};

#endif // WIDGETPACIENTE_H
