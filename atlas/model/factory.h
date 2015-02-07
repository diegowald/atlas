#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include "forward.h"

class Factory : public QObject
{
    Q_OBJECT
public:
    explicit Factory(QObject *parent = 0);
    ~Factory();

    HistoriaClinicaPtr crearNuevaHistoriaClinica();


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
