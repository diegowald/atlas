#ifndef WIDGETPACIENTE_H
#define WIDGETPACIENTE_H

#include <QWidget>
#include "model/forward.h"
#include "mongo/client/dbclient.h"

namespace Ui {
class WidgetPaciente;
}

class WidgetPaciente : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPaciente(QWidget *parent = 0);
    ~WidgetPaciente();
    void setData(PersonaPtr persona, mongo::OID idHistoria);
    void applyData();

    bool esDNIUnico();
private slots:
    void on_dateFechaNacimiento_userDateChanged(const QDate &date);

    void on_txtDocumento_editingFinished();

private:
    Ui::WidgetPaciente *ui;
    PersonaPtr _persona;
    mongo::OID _idHistoria;

    bool _dniUnico;
};

#endif // WIDGETPACIENTE_H
