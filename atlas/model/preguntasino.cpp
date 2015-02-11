#include "preguntasino.h"
#include "../widgets/wdgtsino.h"

PreguntaSiNo::PreguntaSiNo(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, parent)
{

}

PreguntaSiNo::~PreguntaSiNo()
{

}

PreguntaBasePtr PreguntaSiNo::clone()
{
    PreguntaSiNoPtr p = PreguntaSiNoPtr(new PreguntaSiNo(label(), nota(), parent()));
    return p;
}

QWidget* PreguntaSiNo::widget()
{
    return new WdgtSiNo();
}
