#include "preguntacombodoble.h"
#include "../widgets/wdgtcombodoble.h"

PreguntaComboDoble::PreguntaComboDoble(const QString &label, const QString &nota, QStringList &lista1, QStringList &lista2, QObject *parent) : PreguntaBase(label, nota, parent)
{
    _lista1 = lista1;
    _lista2 = lista2;
}

PreguntaComboDoble::~PreguntaComboDoble()
{

}

PreguntaBasePtr PreguntaComboDoble::clone()
{
    PreguntaComboDoblePtr p = PreguntaComboDoblePtr(new PreguntaComboDoble(label(), nota(), _lista1, _lista2, parent()));
    return p;
}

QWidget* PreguntaComboDoble::widget()
{
    WdgtComboDoble *w = new WdgtComboDoble();
    w->setLista1(_lista1);
    w->setLista2(_lista2);
    return w;
}
