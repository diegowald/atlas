#include "preguntatexto.h"
#include <QTextDocument>

PreguntaTexto::PreguntaTexto(const QString &label, const QString &nota, bool showNotes, QObject *parent)
    : PreguntaBase(label, nota, "text", showNotes, parent)
{

}

#ifdef USEMONGO
PreguntaTexto::PreguntaTexto(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj value = obj["value"].Obj();
    _text = value["text"].String().c_str();
}
#else
PreguntaTexto::PreguntaTexto(QJsonObject &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    QJsonObject value = obj["value"].toObject();
    _text = value["text"].toString();
}
#endif

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

#ifdef USEMONGO
mongo::BSONObj PreguntaTexto::value()
{
    mongo::BSONObj obj = BSON("text" << _text.toStdString());
    return obj;
}
#else
QJsonObject PreguntaTexto::value()
{
    QJsonObject obj;
    obj["text"] = _text;
    return obj;
}
#endif


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

QString PreguntaTexto::text() const
{
    return _text;
}
