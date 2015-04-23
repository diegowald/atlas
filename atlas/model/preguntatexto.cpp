#include "preguntatexto.h"
#include <QTextDocument>

PreguntaTexto::PreguntaTexto(const QString &label, const QString &nota, bool showNotes, QObject *parent)
    : PreguntaBase(label, nota, "text", showNotes, parent)
{

}

PreguntaTexto::PreguntaTexto(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _text = value["text"].String().c_str();
}

PreguntaTexto::~PreguntaTexto()
{

}

PreguntaBasePtr PreguntaTexto::clone()
{
    PreguntaTextoPtr p = PreguntaTextoPtr(new PreguntaTexto(label(), nota(), isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaTexto::widget()
{
    _widget = new WdgtTexto(isShowingNotes());
    _widget->setValue(_text);
    _widget->setNotes(nota());
    return _widget;
}

mongo::BSONObj PreguntaTexto::value()
{
    mongo::BSONObj obj = BSON("text" << _text.toStdString());
    return obj;
}

void PreguntaTexto::applyChanges()
{
    _text = _widget->value();
    setNota(_widget->notes());
}

QString PreguntaTexto::toHtml()
{
    return toHtml(true);
}

QString PreguntaTexto::toHtml(bool incluirNotas)
{
    QTextDocument doc;
    doc.setHtml(_text);
    QString text = doc.toPlainText();
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";
    s += QString("<tr><td>%1</td><td>%2</td></tr>").arg(label()).arg(text);
    s += QString("<tr><td colspan=\"2\">%1</td></tr>").arg(nota());
    s += "</table>";
    return s;
}
