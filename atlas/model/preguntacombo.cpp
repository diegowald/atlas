#include "preguntacombo.h"
#include "../widgets/wdgtcombo.h"

PreguntaCombo::PreguntaCombo()
{

}

PreguntaCombo::~PreguntaCombo()
{

}

PreguntaBasePtr PreguntaCombo::clone()
{
    PreguntaComboPtr p = PreguntaComboPtr(new PreguntaCombo());
    return p;
}

QWidget* PreguntaCombo::widget()
{
    return new WdgtCombo();
}
