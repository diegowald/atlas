#include "preguntacombodoble.h"
#include "../widgets/wdgtcombodoble.h"

PreguntaComboDoble::PreguntaComboDoble()
{

}

PreguntaComboDoble::~PreguntaComboDoble()
{

}

PreguntaBasePtr PreguntaComboDoble::clone()
{
    PreguntaComboDoblePtr p = PreguntaComboDoblePtr(new PreguntaComboDoble());
    return p;
}

QWidget* PreguntaComboDoble::widget()
{
    return new WdgtComboDoble();
}
