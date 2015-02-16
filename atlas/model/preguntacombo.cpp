#include "preguntacombo.h"
#include <QDebug>

PreguntaCombo::PreguntaCombo(const QString &label, const QString &nota, QStringList &listaValores, QObject *parent) : PreguntaBase(label, nota, "combo", parent)
{
    _listaValores = listaValores;
}

PreguntaCombo::PreguntaCombo(mongo::BSONObj &obj, QObject *parent) : PreguntaBase(obj, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    qDebug() << value.jsonString().c_str();
    mongo::BSONObj objValues = value["values"].Obj();
    std::vector<mongo::BSONElement> values;
    objValues.elems(values);
    for (std::vector<mongo::BSONElement>::iterator it = values.begin(); it != values.end(); ++it)
    {
        _listaValores.append(it->String().c_str());
    }
    _selectedValue = value["selected"].String().c_str();
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
    _widget = new WdgtCombo();
    _widget->setLista(_listaValores);
    return _widget;
}

mongo::BSONObj PreguntaCombo::value()
{
    mongo::BSONArrayBuilder builder;
    foreach (QString pregunta, _listaValores)
    {
        builder.append(pregunta.toStdString());
    }
    mongo::BSONObj obj = BSON("values" << builder.arr()
                              << "selected" << _selectedValue.toStdString());
    return obj;
}

void PreguntaCombo::applyChanges()
{
    _selectedValue = _widget->value();
}
