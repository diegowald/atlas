#ifndef WIDGETPACIENTE_H
#define WIDGETPACIENTE_H

#include <QWidget>
#include "model/forward.h"


#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

#ifdef USEMONGO
#include <mongo/client/dbclient.h>
#else
#endif

#include "util/resaltadortexto.h"


namespace Ui {
class WidgetPaciente;
}

class WidgetPaciente : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPaciente(QWidget *parent = 0);
    ~WidgetPaciente();
#ifdef USEMONGO
    void setData(PersonaPtr persona, mongo::OID idHistoria);
#else
    void setData(PersonaPtr persona, const QString &idHistoria);
#endif
    void applyData();

    bool esDNIUnico();
private slots:
    void on_dateFechaNacimiento_userDateChanged(const QDate &date);

    void on_txtDocumento_editingFinished();

private:
    Ui::WidgetPaciente *ui;
    PersonaPtr _persona;
#ifdef USEMONGO
    mongo::OID _idHistoria;
#else
    QString _idHistoria;
#endif
    ResaltadorTexto *_resaltador;

    bool _dniUnico;
};

#endif // WIDGETPACIENTE_H
