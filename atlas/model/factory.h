#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include "forward.h"

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

#ifdef USEMONGO
#ifdef WIN32
#include <mongo/client/dbclient.h>
#else
#include "mongo/client/dbclient.h"
#endif
#else
#include <QJsonObject>
#endif

class Factory : public QObject
{
    Q_OBJECT

public:
    ~Factory();
    explicit Factory(QObject *parent = NULL);

    HistoriaClinicaPtr crearNuevaHistoriaClinica();

#if USEMONGO
    HistoriaClinicaPtr crearHistoria(mongo::BSONObj &obj);
    static PreguntaBasePtr crearPregunta(mongo::BSONObj &obj, bool showNotes);
    static AlarmaPtr crearAlarma(mongo::BSONObj &obj);
#else
    HistoriaClinicaPtr crearHistoria(QJsonObject &obj);
    static PreguntaBasePtr crearPregunta(QJsonObject &obj, bool showNotes);
    static AlarmaPtr crearAlarma(QJsonObject &obj);
#endif

    static AlarmaPtr crearNuevaAlarma(HistoriaClinicaPtr historia);

    static ReporteBasePtr crearDatoReporte(PreguntaBasePtr pregunta);

protected:
    PersonaPtr crearPersona();
    QList<PreguntaBasePtr> cloneAntecedentes();
    QList<PreguntaBasePtr> cloneTestKinesiologico();
    QList<PreguntaBasePtr> cloneCuestionario();

    void cargarAntecedentes();
    void cargarTestKinesiologico();
    void cargarCuestionario();

signals:

public slots:

private:
    QList<PreguntaBasePtr> _templateAntecedentes;
    QList<PreguntaBasePtr> _templateTestKinesiologico;
    QList<PreguntaBasePtr> _templateCuestionario;
};

#endif // FACTORY_H
