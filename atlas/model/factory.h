  #ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include "forward.h"
#include <mongo/client/dbclient.h>


class Factory : public QObject
{
    Q_OBJECT

public:
    ~Factory();
    explicit Factory(QObject *parent = NULL);

    HistoriaClinicaPtr crearNuevaHistoriaClinica();
    HistoriaClinicaPtr crearHistoria(mongo::BSONObj &obj);

    static PreguntaBasePtr crearPregunta(mongo::BSONObj &obj);

    static AlarmaPtr crearAlarma(mongo::BSONObj &obj);
    static AlarmaPtr crearNuevaAlarma(HistoriaClinicaPtr historia);

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
