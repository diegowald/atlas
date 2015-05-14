#include "reportepreguntacombodoble.h"
#include "../model/preguntacombodoble.h"

ReportePreguntaComboDoble::ReportePreguntaComboDoble(PreguntaBasePtr pregunta, QObject *parent) :
    ReporteBase(pregunta, parent)
{
    PreguntaComboDoblePtr preg = pregunta.staticCast<PreguntaComboDoble>();
    QStringList opciones1 = preg->opciones1();
    QStringList opciones2 = preg->opciones2();
    foreach (QString opcion1, opciones1)
    {
        foreach (QString opcion2, opciones2)
        {
            _counterOpciones[opcion1][opcion2] = SumarizadorPtr(new Sumarizador(opcion1 + "." + opcion2));
        }
    }
    add(pregunta);
}

ReportePreguntaComboDoble::~ReportePreguntaComboDoble()
{
}

void ReportePreguntaComboDoble::add(PreguntaBasePtr pregunta)
{
    PreguntaComboDoblePtr preg = pregunta.staticCast<PreguntaComboDoble>();
    QString opcion1 = preg->option1Selected();
    QString opcion2 = preg->option2Selected();
    if (_counterOpciones.contains(opcion1) && _counterOpciones[opcion1].contains(opcion2))
    {
        _counterOpciones[opcion1][opcion2]->increment();
    }
    else
    {
        _counterOpciones[opcion1][opcion2] = SumarizadorPtr(new Sumarizador(opcion1 + "." + opcion2));
    }
    _counter->increment();
}


QString ReportePreguntaComboDoble::stats(int total)
{
    QString html = "Cantidad de preguntas: " + QString::number(_counter->count())
            + " -> " + QString::number((double)_counter->count() / total * 100.0) + "%<br>";
    foreach(QString key, _counterOpciones.keys())
    {
        foreach(QString key2, _counterOpciones[key].keys())
        {
            SumarizadorPtr ctr = _counterOpciones[key][key2];
            html += key + ", " + key2 + ": " + QString::number(ctr->count())
                    + " -> " + QString::number((double)ctr->count() / total * 100.0) + "%<br>";
        }
    }
    return html;
}
