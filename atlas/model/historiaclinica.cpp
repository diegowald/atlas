#include "historiaclinica.h"

HistoriaClinica::HistoriaClinica(PersonaPtr persona,
                                 QList<PreguntaBasePtr> &templateAntecedentes,
                                 QList<PreguntaBasePtr> &templateCuestionario,
                                 QObject *parent) : QObject(parent)
{
    _persona = persona;
    _antecedentes = templateAntecedentes;
    _cuestionario = templateCuestionario;
}

HistoriaClinica::~HistoriaClinica()
{

}

