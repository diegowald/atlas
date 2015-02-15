#include "preguntacombodoble.h"

PreguntaComboDoble::PreguntaComboDoble(const QString &label, const QString &nota, QStringList &lista1, QStringList &lista2, QObject *parent) : PreguntaBase(label, nota, "combodoble", parent)
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
    _widget = new WdgtComboDoble();
    _widget->setLista1(_lista1);
    _widget->setLista2(_lista2);
    return _widget;
}

mongo::BSONObj PreguntaComboDoble::value()
{
    mongo::BSONArrayBuilder builder1;
    foreach (QString pregunta, _lista1)
    {
        builder1.append(pregunta.toStdString());
    }

    mongo::BSONArrayBuilder builder2;
    foreach (QString pregunta, _lista2)
    {
        builder2.append(pregunta.toStdString());
    }

    mongo::BSONObj obj = BSON("values1" << builder1.arr()
                              << "selected1" << _selected1.toStdString()
                              << "values2" << builder2.arr()
                              << "selected2" << _selected2.toStdString());
    return obj;
}

void PreguntaComboDoble::applyChanges()
{
    _selected1 = _widget->value1();
    _selected2 = _widget->value2();
}
