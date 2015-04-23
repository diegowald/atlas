#include "preguntacheckbox.h"

PreguntaCheckBox::PreguntaCheckBox(const QString &label, const QString &nota, bool showNotes, QObject *parent)
    : PreguntaBase(label, nota, "checkbox", showNotes, parent)
{
    _checked = false;
}

PreguntaCheckBox::PreguntaCheckBox(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _checked = value["checked"].Bool();
}

PreguntaCheckBox::~PreguntaCheckBox()
{

}

PreguntaBasePtr PreguntaCheckBox::clone()
{
    PreguntaCheckBoxPtr p = PreguntaCheckBoxPtr(new PreguntaCheckBox(label(), nota(), isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaCheckBox::widget()
{
    _widget = new WdgtCheckBox(isShowingNotes());
    _widget->setValue(_checked);
    _widget->setNotes(nota());
    return _widget;
}

mongo::BSONObj PreguntaCheckBox::value()
{
    mongo::BSONObj obj = BSON("checked" << _checked);
    return obj;
}

void PreguntaCheckBox::applyChanges()
{
    _checked = _widget->value();
    setNota(_widget->notes());
}

QString PreguntaCheckBox::toHtml()
{
    return toHtml(true);
}

QString PreguntaCheckBox::toHtml(bool incluirNotas)
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";
    s += QString("<tr><td>%1</td><td>%2</td></tr>").arg(label()).arg(_checked ? "Sí" : "No");
    if (incluirNotas)
        s += QString("<tr><td colspan=\"2\">%1</td></tr>").arg(nota());
    s += "</table>";
    return s;
}
