#include "preguntacombodoble.h"
#include <QJsonArray>


PreguntaComboDoble::PreguntaComboDoble(const QString &label, const QString &nota, QStringList &lista1, QStringList &lista2, bool showNotes, QObject *parent) : PreguntaBase(label, nota, "combodoble", showNotes, parent)
{
    _lista1 = lista1;
    _lista2 = lista2;
}

#ifdef USEMONGO
PreguntaComboDoble::PreguntaComboDoble(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    mongo::BSONObj objValues = value["values1"].Obj();
    std::vector<mongo::BSONElement> values;
    objValues.elems(values);
    for (std::vector<mongo::BSONElement>::iterator it = values.begin(); it != values.end(); ++it)
    {
        _lista1.append(it->String().c_str());
    }
    _selected1 = value["selected1"].String().c_str();

    objValues = value["values2"].Obj();
    values.clear();
    objValues.elems(values);
    for (std::vector<mongo::BSONElement>::iterator it = values.begin(); it != values.end(); ++it)
    {
        _lista2.append(it->String().c_str());
    }
    _selected2 = value["selected2"].String().c_str();
}
#else
PreguntaComboDoble::PreguntaComboDoble(QJsonObject &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, parent)
{
    QJsonObject value = obj["value"].toObject();
    QJsonArray objValues = value["values1"].toArray();
    for (int i = 0; i < objValues.count(); ++i)
    {
        _lista1.append(objValues[i].toString());
    }
    _selected1 = value["selected1"].toString();

    objValues = value["values2"].toArray();
    for (int i = 0; i < objValues.count(); ++i)
    {
        _lista2.append(objValues[i].toString());
    }
    _selected2 = value["selected2"].toString();
}
#endif

PreguntaComboDoble::~PreguntaComboDoble()
{

}

PreguntaBasePtr PreguntaComboDoble::clone()
{
    PreguntaComboDoblePtr p = PreguntaComboDoblePtr(new PreguntaComboDoble(label(), nota(), _lista1, _lista2, isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaComboDoble::widget()
{
    _widget = new WdgtComboDoble(isShowingNotes());
    _widget->setLista1(_lista1);
    _widget->setLista2(_lista2);
    _widget->setValue1(_selected1);
    _widget->setValue2(_selected2);
    _widget->setNotes(nota());
    return _widget;
}

#ifdef USEMONGO
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
#else
QJsonObject PreguntaComboDoble::value()
{
    QJsonArray builder1;
    foreach (QString pregunta, _lista1)
    {
        builder1.append(pregunta);
    }

    QJsonArray builder2;
    foreach (QString pregunta, _lista2)
    {
        builder2.append(pregunta);
    }

    QJsonObject obj;
    obj["values1"] = builder1;
    obj["selected1"] = _selected1;
    obj["values2"] = builder2;
    obj["selected2"] = _selected2;
    return obj;
}
#endif

void PreguntaComboDoble::applyChanges()
{
    _selected1 = _widget->value1();
    _selected2 = _widget->value2();
    setNota(_widget->notes());
}

QString PreguntaComboDoble::toHtml()
{
    return toHtml(true);
}

QString PreguntaComboDoble::toHtml(bool incluirNotas)
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";
    s += QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>").arg(label()).arg(_selected1).arg(_selected2);
    if (incluirNotas)
        s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(nota());
    s += "</table>";
    return s;
}

QStringList PreguntaComboDoble::opciones1()
{
    return _lista1;
}

QStringList PreguntaComboDoble::opciones2()
{
    return _lista2;
}

QString PreguntaComboDoble::option1Selected() const
{
    return _selected1;
}

QString PreguntaComboDoble::option2Selected() const
{
    return _selected2;
}
