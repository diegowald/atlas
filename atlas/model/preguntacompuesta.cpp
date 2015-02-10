#include "preguntacompuesta.h"
#include "../widgets/wdgtcompuesto.h"

PreguntaCompuesta::PreguntaCompuesta()
{

}

PreguntaCompuesta::~PreguntaCompuesta()
{

}

PreguntaBasePtr PreguntaCompuesta::clone()
{
    PreguntaCompuestaPtr p = PreguntaCompuestaPtr(new PreguntaCompuesta());
    foreach (PreguntaBasePtr pb, _subPreguntas)
    {
        p->_subPreguntas.append(pb->clone());
    }
    return p;
}

QWidget* PreguntaCompuesta::widget()
{
    WdgtCompuesto* wdg = new WdgtCompuesto();
    foreach (PreguntaBasePtr preg, _subPreguntas)
    {
        wdg->addPregunta(preg);
    }
    return wdg;
}
