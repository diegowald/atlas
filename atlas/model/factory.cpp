#include "factory.h"
#include "historiaclinica.h"
#include "persona.h"
#include "preguntabase.h"
#include "preguntacheckbox.h"
#include "preguntacombo.h"
#include "preguntacombodoble.h"
#include "preguntacompuesta.h"
#include "preguntasino.h"
#include "preguntatexto.h"

Factory::Factory(QObject *parent) : QObject(parent)
{
    cargarAntecedentes();
    cargarCuestionario();
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
    _templateAntecedentes.clear();
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox()));
    _templateAntecedentes.append(PreguntaComboPtr(new PreguntaCombo()));
    _templateAntecedentes.append(PreguntaComboDoblePtr(new PreguntaComboDoble()));
    _templateAntecedentes.append(PreguntaCompuestaPtr(new PreguntaCompuesta()));
    _templateAntecedentes.append(PreguntaSiNoPtr(new PreguntaSiNo()));
    _templateAntecedentes.append(PreguntaTextoPtr(new PreguntaTexto()));
}

void Factory::cargarCuestionario()
{
}
