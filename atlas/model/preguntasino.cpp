#include "preguntasino.h"
#include "../widgets/wdgtsino.h"

PreguntaSiNo::PreguntaSiNo(const QString &label, const QString &nota, bool showNotes, QObject *parent) : PreguntaBase(label, nota, "yesno", showNotes, parent)
{

}

PreguntaSiNo::PreguntaSiNo(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _value = value["value"].Bool();
}

PreguntaSiNo::~PreguntaSiNo()
{

}

PreguntaBasePtr PreguntaSiNo::clone()
{
    PreguntaSiNoPtr p = PreguntaSiNoPtr(new PreguntaSiNo(label(), nota(), isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaSiNo::widget()
{
    _widget = new WdgtSiNo(isShowingNotes());
    _widget->setValue(_value);
    _widget->setNotes(nota());
    return _widget;
}

mongo::BSONObj PreguntaSiNo::value()
{
    mongo::BSONObj obj = BSON("value" << _value);
    return obj;
}

void PreguntaSiNo::applyChanges()
{
    _value = _widget->value();
    setNota(_widget->notes());
}

QString PreguntaSiNo::toHtml()
{
    return toHtml(true);
}

QString PreguntaSiNo::toHtml(bool incluirNotas)
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";
    s += QString("<tr><td>%1</td><td>%2</td></tr>").arg(label()).arg(_value ? "Sí" : "No");
    if (incluirNotas)
        s += QString("<tr><td colspan=\"2\">%1</td></tr>").arg(nota());
    s += "</table>";
    return s;
}

bool PreguntaSiNo::isYes() const
{
    return _value;
}
