#include "reportepreguntacombo.h"
#include "../model/preguntacombo.h"
#include "sumarizador.h"

ReportePreguntaCombo::ReportePreguntaCombo(PreguntaBasePtr pregunta, QObject *parent) :
    ReporteBase(pregunta, parent)
{
    PreguntaComboPtr preg = pregunta.staticCast<PreguntaCombo>();
    foreach(QString opcion, preg->opciones())
    {
        _opciones[opcion] = SumarizadorPtr(new Sumarizador(opcion));
    }
    add(pregunta);
}

ReportePreguntaCombo::~ReportePreguntaCombo()
{
}

void ReportePreguntaCombo::add(PreguntaBasePtr pregunta)
{
    PreguntaComboPtr preg = pregunta.staticCast<PreguntaCombo>();
    QString opcion = preg->optionSelected();
    if (_opciones.contains(opcion))
    {
        _opciones[opcion]->increment();
    }
    else
    {
        _opciones[opcion] = SumarizadorPtr(new Sumarizador(opcion));
        _opciones[opcion]->increment();
    }
    _counter->increment();
}

QString ReportePreguntaCombo::stats(int total)
{
    QString html = "Cantidad de preguntas: " + QString::number(_counter->count())
            + " -> " + QString::number((double)_counter->count() / total * 100.0) + "%<br>";
    foreach(QString key, _opciones.keys())
    {
        SumarizadorPtr ctr = _opciones[key];
        html += key + ": " + QString::number(ctr->count())
                + " -> " + QString::number((double)ctr->count() / total * 100.0) + "%<br>";
    }
    return html;
}
