#include "preguntacheckbox.h"
#include "../widgets/wdgtcheckbox.h"

PreguntaCheckBox::PreguntaCheckBox(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, parent)
{

}

PreguntaCheckBox::~PreguntaCheckBox()
{

}

PreguntaBasePtr PreguntaCheckBox::clone()
{
    PreguntaCheckBoxPtr p = PreguntaCheckBoxPtr(new PreguntaCheckBox(label(), nota(), parent()));
    return p;
}

QWidget* PreguntaCheckBox::widget()
{
    return new WdgtCheckBox();
}
