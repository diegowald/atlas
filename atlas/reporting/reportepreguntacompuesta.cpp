#include "reportepreguntacompuesta.h"
#include "../model/preguntabase.h"
#include "../model/preguntacompuesta.h"
#include "../model/factory.h"

ReportePreguntaCompuesta::ReportePreguntaCompuesta(PreguntaBasePtr pregunta, QObject *parent) :
    ReporteBase(pregunta, parent)
{
    PreguntaCompuestaPtr preg = pregunta.staticCast<PreguntaCompuesta>();

    foreach (PreguntaBasePtr p, preg->subPreguntas())
    {
        ReporteBasePtr rpt = Factory::crearDatoReporte(p);
        _subReportes[p->label()] = rpt;
    }
    add(pregunta);
}

ReportePreguntaCompuesta::~ReportePreguntaCompuesta()
{
}

void ReportePreguntaCompuesta::add(PreguntaBasePtr pregunta)
{
    PreguntaCompuestaPtr preg = pregunta.staticCast<PreguntaCompuesta>();
    if (preg->isChecked())
    {
        _counter->increment();
        foreach (PreguntaBasePtr p, preg->subPreguntas())
        {
            if (_subReportes.contains(p->label()))
            {
                _subReportes[p->label()]->add(p);
            }
            else
            {
                ReporteBasePtr rpt = Factory::crearDatoReporte(p);
                _subReportes[p->label()] = rpt;
            }
        }
    }
}


QString ReportePreguntaCompuesta::stats(int total)
{
    QString html = "Cantidad de preguntas: " + QString::number(_counter->count())
            + " -> " + QString::number(_counter->count() / total * 100) + "%<br>";
    foreach(QString key, _subReportes.keys())
    {
        ReporteBasePtr rpt = _subReportes[key];
        html += key + ": <br>";
        html += rpt->stats(total);
    }
    return html;
}
