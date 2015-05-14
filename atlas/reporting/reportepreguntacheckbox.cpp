#include "reportepreguntacheckbox.h"
#include "../model/preguntacheckbox.h"

ReportePreguntaCheckBox::ReportePreguntaCheckBox(PreguntaBasePtr pregunta, QObject *parent) :
    ReporteBase(pregunta, parent)
{
    _checked = SumarizadorPtr(new Sumarizador("Checked"));
    _unchecked = SumarizadorPtr(new Sumarizador("Unchecked"));
    add(pregunta);
}

ReportePreguntaCheckBox::~ReportePreguntaCheckBox()
{
}

void ReportePreguntaCheckBox::add(PreguntaBasePtr pregunta)
{
    PreguntaCheckBoxPtr preg = pregunta.staticCast<PreguntaCheckBox>();
    if (preg->isChecked())
        _checked->increment();
    else
        _unchecked->increment();
    _counter->increment();
}

QString ReportePreguntaCheckBox::stats(int total)
{
    QString html = "Cantidad de preguntas: " + QString::number(_counter->count())
            + " -> " + QString::number((double)_counter->count() / total * 100.0) + "%<br>";
    html += "Seleccionado: " + QString::number(_checked->count())
            + " -> " + QString::number((double)_checked->count() / total * 100.0) + "%<br>";
    html += "No seleccionado: " + QString::number(_unchecked->count())
            + " -> " + QString::number((double)_unchecked->count() / total * 100.0) + "%<br>";
    return html;
}
