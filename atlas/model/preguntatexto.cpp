#include "preguntatexto.h"

PreguntaTexto::PreguntaTexto(const QString &label, const QString &nota, QObject *parent) : PreguntaBase(label, nota, "text", parent)
{

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
