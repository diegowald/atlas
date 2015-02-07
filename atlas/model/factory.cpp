#include "factory.h"
#include "historiaclinica.h"
#include "persona.h"
#include "preguntabase.h"

Factory::Factory(QObject *parent) : QObject(parent)
{

}

Factory::~Factory()
{

}

HistoriaClinicaPtr Factory::crearNuevaHistoriaClinica()
{
    QList<PreguntaBasePtr> antecedentes = cloneAntecedentes();
    QList<PreguntaBasePtr> cuestionario = cloneCuestionario();

    HistoriaClinicaPtr hist = HistoriaClinicaPtr::create(crearPersona(), antecedentes, cuestionario);
    return hist;
}

PersonaPtr Factory::crearPersona()
{
    PersonaPtr persona = PersonaPtr::create();
    return persona;
}

QList<PreguntaBasePtr> Factory::cloneAntecedentes()
{
    QList<PreguntaBasePtr> ant;
    foreach (PreguntaBasePtr preg, _templateAntecedentes)
    {
        ant.append(preg->clone());
    }
    return ant;
}

QList<PreguntaBasePtr> Factory::cloneCuestionario()
{
     QList<PreguntaBasePtr> cuest;
     foreach (PreguntaBasePtr preg, _templateCuestionario)
     {
         cuest.append(preg->clone());
     }
     return cuest;
}

void Factory::cargarAntecedentes()
{
}

void Factory::cargarCuestionario()
{
}
