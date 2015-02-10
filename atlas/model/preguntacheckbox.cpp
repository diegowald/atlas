#include "preguntacheckbox.h"
#include "../widgets/wdgtcheckbox.h"

PreguntaCheckBox::PreguntaCheckBox()
{

}

PreguntaCheckBox::~PreguntaCheckBox()
{

}

PreguntaBasePtr PreguntaCheckBox::clone()
{
    PreguntaCheckBoxPtr p = PreguntaCheckBoxPtr(new PreguntaCheckBox());
    return p;
}

QWidget* PreguntaCheckBox::widget()
{
    return new WdgtCheckBox();
}
