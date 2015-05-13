#include "reportebase.h"
#include "../model/preguntabase.h"

ReporteBase::ReporteBase(PreguntaBasePtr pregunta, QObject *parent) : QObject(parent)
{
    _counter = SumarizadorPtr(new Sumarizador(pregunta->label()));
    _preguntas.append(pregunta);
}

ReporteBase::~ReporteBase()
{
}
