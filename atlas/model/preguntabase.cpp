#include "preguntabase.h"
#include "../widgets/wdgtwithlabel.h"

PreguntaBase::PreguntaBase(const QString &label, const QString &nota, const QString &type, bool showNotes, QObject *parent) : QObject(parent)
{
    _label = label;
    _nota = nota;
    _type = type;
    _showNotes = showNotes;
}

PreguntaBase::PreguntaBase(mongo::BSONObj &obj, bool showNotes, QObject *parent)
{
    _label = obj["label"].String().c_str();
    _nota = obj["nota"].String().c_str();
    _type = obj["type"].String().c_str();
    _showNotes = showNotes;
}

PreguntaBase::~PreguntaBase()
{

}

void PreguntaBase::setLabel(const QString &Label)
{
    _label = Label;
}

void PreguntaBase::setNota(const QString &Nota)
{
    _nota = Nota;
}

QString PreguntaBase::label() const
{
    return _label;
}

QString PreguntaBase::nota() const
{
    return _nota;
}

QWidget *PreguntaBase::widget(bool includeLabel)
{
    return includeLabel ? widgetWithLabel() : widget();
}

QWidget *PreguntaBase::widgetWithLabel()
{
    WdgtWithLabel *wdget = new WdgtWithLabel(isShowingNotes());
    wdget->addWidget(_label, widget());
    return wdget;
}

mongo::BSONObj PreguntaBase::toBson()
{
    mongo::BSONObj obj = BSON(
                "label" << _label.toStdString()
                << "nota" << _nota.toStdString()
                << "type" << _type.toStdString()
                << "value" << value());
    return obj;
}

bool PreguntaBase::isShowingNotes() const
{
    return _showNotes;
}
