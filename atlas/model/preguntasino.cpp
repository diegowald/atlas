#include "preguntasino.h"
#include "../widgets/wdgtsino.h"

PreguntaSiNo::PreguntaSiNo()
{

}

PreguntaSiNo::~PreguntaSiNo()
{

}

PreguntaBasePtr PreguntaSiNo::clone()
{
    PreguntaSiNoPtr p = PreguntaSiNoPtr(new PreguntaSiNo());
    return p;
}

QWidget* PreguntaSiNo::widget()
{
    return new WdgtSiNo();
}
