#include "preguntabase.h"

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
