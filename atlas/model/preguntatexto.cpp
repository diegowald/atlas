#include "preguntatexto.h"

PreguntaTexto::PreguntaTexto(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, "text", parent)
{

}

PreguntaTexto::PreguntaTexto(mongo::BSONObj &obj, QObject *parent) : PreguntaBase(obj, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _text = value["text"].String().c_str();
}

PreguntaTexto::~PreguntaTexto()
{

}

PreguntaBasePtr PreguntaTexto::clone()
{
    PreguntaTextoPtr p = PreguntaTextoPtr(new PreguntaTexto(label(), nota(), parent()));
    return p;
}

QWidget* PreguntaTexto::widget()
{
    _widget = new WdgtTexto();
    _widget->setValue(_text);
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
}
