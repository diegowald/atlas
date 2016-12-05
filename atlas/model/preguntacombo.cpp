#include "preguntacombo.h"
#include <QJsonArray>

PreguntaCombo::PreguntaCombo(const QString &label, const QString &nota, QStringList &listaValores, bool showNotes, QObject *parent)
    : PreguntaBase(label, nota, "combo", showNotes, parent)
{
    _listaValores = listaValores;
}

#ifdef USEMONGO
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
#else
PreguntaCombo::PreguntaCombo(QJsonObject &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    QJsonObject value = obj["value"].toObject();
    QJsonArray objValues = value["values"].toArray();

    for (int i = 0; i < objValues.count(); ++i)
    {
        _listaValores.append(objValues[i].toString());
    }
    _selectedValue = value["selected"].toString();
}
#endif

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

#ifdef USEMONGO
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
#else
QJsonObject PreguntaCombo::value()
{
    QJsonArray builder;
    foreach (QString pregunta, _listaValores)
    {
        builder.append(pregunta);
    }
    QJsonObject obj;
    obj["values"] = builder;
    obj["selected"] = _selectedValue;
    return obj;
}
#endif

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

QString PreguntaCombo::optionSelected() const
{
    return _selectedValue;
}

QStringList PreguntaCombo::opciones()
{
    return _listaValores;
}
