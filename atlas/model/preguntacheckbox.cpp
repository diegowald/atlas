#include "preguntacheckbox.h"

PreguntaCheckBox::PreguntaCheckBox(const QString &label, const QString &nota, bool showNotes, QObject *parent)
    : PreguntaBase(label, nota, "checkbox", showNotes, parent)
{

}

PreguntaCheckBox::PreguntaCheckBox(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _checked = value["checked"].Bool();
}

PreguntaCheckBox::~PreguntaCheckBox()
{

}

PreguntaBasePtr PreguntaCheckBox::clone()
{
    PreguntaCheckBoxPtr p = PreguntaCheckBoxPtr(new PreguntaCheckBox(label(), nota(), isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaCheckBox::widget()
{
    _widget = new WdgtCheckBox(isShowingNotes());
    _widget->setValue(_checked);
    _widget->setNotes(nota());
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
    setNota(_widget->notes());
}
