#include "sumarizador.h"

Sumarizador::Sumarizador(const QString &label, QObject *parent) : QObject(parent)
{
    _label = label;
    _count = 0;
}

void Sumarizador::increment()
{
    _count++;
}

int Sumarizador::count()
{
    return _count;
}


