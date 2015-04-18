#include "preguntatexto.h"

PreguntaTexto::PreguntaTexto(const QString &label, const QString &nota, bool showNotes, QObject *parent)
    : PreguntaBase(label, nota, "text", showNotes, parent)
{

}

PreguntaTexto::PreguntaTexto(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _text = value["text"].String().c_str();
}

PreguntaTexto::~PreguntaTexto()
{

}

PreguntaBasePtr PreguntaTexto::clone()
{
    PreguntaTextoPtr p = PreguntaTextoPtr(new PreguntaTexto(label(), nota(), isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaTexto::widget()
{
    _widget = new WdgtTexto(isShowingNotes());
    _widget->setValue(_text);
    _widget->setNotes(nota());
    return _widget;
}

mongo::BSONObj PreguntaTexto::value()
{
    mongo::BSONObj obj = BSON("text" << _text.toStdString());
    return obj;
}

void PreguntaTexto::applyChanges()
{
    _text = _widget->value();
    setNota(_widget->notes());
}
