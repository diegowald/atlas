#include "preguntatexto.h"
#include "../widgets/wdgttexto.h"

PreguntaTexto::PreguntaTexto(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, parent)
{

}

PreguntaTexto::~PreguntaTexto()
{

}

PreguntaBasePtr PreguntaTexto::clone()
{
    PreguntaTextoPtr p = PreguntaTextoPtr(new PreguntaTexto(label(), nota(), parent()));
    return p;
}

QWidget* PreguntaTexto::widget()
{
    return new WdgtTexto();
}
