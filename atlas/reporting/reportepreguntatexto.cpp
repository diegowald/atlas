#include "reportepreguntatexto.h"
#include "../model/preguntatexto.h"

ReportePreguntaTexto::ReportePreguntaTexto(PreguntaBasePtr pregunta, QObject *parent) :
    ReporteBase(pregunta, parent)
{
    _counterVacios = SumarizadorPtr(new Sumarizador("Vacíos"));
    _counterNoVacios = SumarizadorPtr(new Sumarizador("Con texto"));
    add(pregunta);
}

ReportePreguntaTexto::~ReportePreguntaTexto()
{
}

void ReportePreguntaTexto::add(PreguntaBasePtr pregunta)
{
    PreguntaTextoPtr preg = pregunta.staticCast<PreguntaTexto>();
    if (0 < preg->text().length())
        _counterNoVacios->increment();
    else
        _counterVacios->increment();
    _counter->increment();
}

QString ReportePreguntaTexto::stats(int total)
{
    QString html = "Cantidad de preguntas: " + QString::number(_counter->count())
            + " -> " + QString::number((double)_counter->count() / total * 100.0) + "%<br>";
    html += "Con Texto introducido: " + QString::number(_counterNoVacios->count())
            + " -> " + QString::number((double)_counterNoVacios->count() / total * 100.0) + "%<br>";
    html += "Sin texts: " + QString::number(_counterVacios->count())
            + " -> " + QString::number((double)_counterVacios->count() / total * 100.0) + "%<br>";
    return html;
}
