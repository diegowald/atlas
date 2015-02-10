#include "preguntatexto.h"
#include "../widgets/wdgttexto.h"

PreguntaTexto::PreguntaTexto()
{

}

PreguntaTexto::~PreguntaTexto()
{

}

PreguntaBasePtr PreguntaTexto::clone()
{
    PreguntaTextoPtr p = PreguntaTextoPtr(new PreguntaTexto());
    return p;
}

QWidget* PreguntaTexto::widget()
{
    return new WdgtTexto();
}
