#include "preguntacombo.h"
#include "../widgets/wdgtcombo.h"

PreguntaCombo::PreguntaCombo(const QString &label, const QString &nota, QStringList &listaValores, QObject *parent) : PreguntaBase(label, nota, parent)
{
    _listaValores = listaValores;
}

PreguntaCombo::~PreguntaCombo()
{

}

PreguntaBasePtr PreguntaCombo::clone()
{
    PreguntaComboPtr p = PreguntaComboPtr(new PreguntaCombo(label(), nota(), _listaValores, parent()));
    return p;
}

QWidget* PreguntaCombo::widget()
{
    WdgtCombo *w = new WdgtCombo();
    w->setLista(_listaValores);
    return w;
}
