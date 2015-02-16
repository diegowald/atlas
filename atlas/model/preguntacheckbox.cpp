#include "preguntacheckbox.h"

PreguntaCheckBox::PreguntaCheckBox(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, "checkbox", parent)
{

}

PreguntaCheckBox::PreguntaCheckBox(mongo::BSONObj &obj, QObject *parent) : PreguntaBase(obj, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _checked = value["checked"].Bool();
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
    _widget = new WdgtCheckBox();
    return _widget;
}

mongo::BSONObj PreguntaCheckBox::value()
{
    mongo::BSONObj obj = BSON("checked" << _checked);
    return obj;
}

void PreguntaCheckBox::applyChanges()
{
    _checked = _widget->value();
}
