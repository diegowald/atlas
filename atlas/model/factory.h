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

protected:
    PersonaPtr crearPersona();
    QList<PreguntaBasePtr> cloneAntecedentes();
    QList<PreguntaBasePtr> cloneCuestionario();

    void cargarAntecedentes();
    void cargarCuestionario();

signals:

public slots:

private:
    QList<PreguntaBasePtr> _templateAntecedentes;
    QList<PreguntaBasePtr> _templateCuestionario;
};

#endif // FACTORY_H
