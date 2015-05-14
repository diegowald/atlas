#include "reportepreguntasino.h"
#include "../model/preguntasino.h"

ReportePreguntaSiNo::ReportePreguntaSiNo(PreguntaBasePtr pregunta, QObject *parent) :
    ReporteBase(pregunta, parent)
{
    PreguntaSiNoPtr preg = pregunta.staticCast<PreguntaSiNo>();
    _counterYes = SumarizadorPtr(new Sumarizador("Sí"));
    _counterNo = SumarizadorPtr(new Sumarizador("No"));
    add(pregunta);
}

ReportePreguntaSiNo::~ReportePreguntaSiNo()
{

}

void ReportePreguntaSiNo::add(PreguntaBasePtr pregunta)
{
    PreguntaSiNoPtr preg = pregunta.staticCast<PreguntaSiNo>();
    if (preg->isYes())
        _counterYes->increment();
    else
        _counterNo->increment();
    _counter->increment();
}


QString ReportePreguntaSiNo::stats(int total)
{
    QString html = "Cantidad de preguntas: " + QString::number(_counter->count())
            + " -> " + QString::number((double)_counter->count() / total * 100.0) + "%<br>";
    html += "Si: " + QString::number(_counterYes->count())
            + " -> " + QString::number((double)_counterYes->count() / total * 100.0) + "%<br>";
    html += "No: " + QString::number(_counterNo->count())
            + " -> " + QString::number((double)_counterNo->count() / total * 100.0) + "%<br>";
    return html;
}
