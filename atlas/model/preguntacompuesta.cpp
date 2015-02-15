#include "preguntacompuesta.h"
#include "../widgets/wdgtcompuesto.h"

PreguntaCompuesta::PreguntaCompuesta(const QString &label, const QString &nota, QList<PreguntaBasePtr> &subpreguntas, QObject *parent) : PreguntaBase(label, nota, "compuesta", parent)
{
    foreach (PreguntaBasePtr pb, subpreguntas)
    {
        _subPreguntas.append(pb->clone());
    }
}

PreguntaCompuesta::~PreguntaCompuesta()
{

}

PreguntaBasePtr PreguntaCompuesta::clone()
{
    PreguntaCompuestaPtr p = PreguntaCompuestaPtr(new PreguntaCompuesta(label(), nota(), _subPreguntas, parent()));
    return p;
}

QWidget* PreguntaCompuesta::widget()
{
    WdgtCompuesto* wdg = new WdgtCompuesto();
    wdg->setLabel(label());
    foreach (PreguntaBasePtr preg, _subPreguntas)
    {
        wdg->addPregunta(preg);
    }
    return wdg;
}

mongo::BSONObj PreguntaCompuesta::value()
{
    mongo::BSONArrayBuilder builder;
    foreach (PreguntaBasePtr pregunta, _subPreguntas)
    {
        builder.append(pregunta->toBson());
    }
    return builder.arr();
}

void PreguntaCompuesta::applyChanges()
{
    foreach (PreguntaBasePtr pregunta, _subPreguntas)
    {
        pregunta->applyChanges();
    }
}
