#include "preguntasino.h"
#include "../widgets/wdgtsino.h"

PreguntaSiNo::PreguntaSiNo(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, "yesno", parent)
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
    _widget = new WdgtSiNo();
    return _widget;
}

mongo::BSONObj PreguntaSiNo::value()
{
    mongo::BSONObj obj = BSON("value" << _value);
    return obj;
}

void PreguntaSiNo::applyChanges()
{
    _value = _widget->value();
}
