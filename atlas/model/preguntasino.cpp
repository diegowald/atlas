#include "preguntasino.h"
#include "../widgets/wdgtsino.h"

PreguntaSiNo::PreguntaSiNo(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, "yesno", parent)
{

}

PreguntaSiNo::PreguntaSiNo(mongo::BSONObj &obj, QObject *parent) : PreguntaBase(obj, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _value = value["value"].Bool();
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
    _widget->setValue(_value);
    _widget->setNotes(nota());
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
    setNota(_widget->notes());
}
