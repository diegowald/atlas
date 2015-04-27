#include "preguntacombo.h"

PreguntaCombo::PreguntaCombo(const QString &label, const QString &nota, QStringList &listaValores, bool showNotes, QObject *parent)
    : PreguntaBase(label, nota, "combo", showNotes, parent)
{
    _listaValores = listaValores;
}

PreguntaCombo::PreguntaCombo(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
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
    PreguntaComboPtr p = PreguntaComboPtr(new PreguntaCombo(label(), nota(), _listaValores, isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaCombo::widget()
{
    _widget = new WdgtCombo(isShowingNotes());
    _widget->setLista(_listaValores);
    _widget->setValue(_selectedValue);
    _widget->setNotes(nota());
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
    setNota(_widget->notes());
}

QString PreguntaCombo::toHtml()
{
    return toHtml(true);
}

QString PreguntaCombo::toHtml(bool incluirNotas)
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\"";
    s += QString("<tr><td>%1</td><td>%2</td></tr>").arg(label()).arg(_selectedValue);
    if (incluirNotas)
        s += QString("<tr><td colspan=\"2\">%1</td></tr>").arg(nota());
    s += "</table>";
    return s;
}
