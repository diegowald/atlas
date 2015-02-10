#include "preguntabase.h"
#include "../widgets/wdgtwithlabel.h"

PreguntaBase::PreguntaBase(QObject *parent) : QObject(parent)
{

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
    WdgtWithLabel *wdget = new WdgtWithLabel();
    wdget->addWidget(_label, widget());
    return wdget;
}
