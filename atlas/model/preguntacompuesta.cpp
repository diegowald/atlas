#include "preguntacompuesta.h"
#include "factory.h"
#include <QJsonArray>

PreguntaCompuesta::PreguntaCompuesta(const QString &label, const QString &nota, QList<PreguntaBasePtr> &subpreguntas, bool showNotes, QObject *parent) : PreguntaBase(label, nota, "compuesta", showNotes, parent)
{
    foreach (PreguntaBasePtr pb, subpreguntas)
    {
        _subPreguntas.append(pb->clone());
    }
    _checked = false;
}

#ifdef USEMONGO
PreguntaCompuesta::PreguntaCompuesta(mongo::BSONObj &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    mongo::BSONObj o = obj["value"].Obj();
    mongo::BSONObj arr = o["questions"].Obj();
    std::vector<mongo::BSONElement> elements;
    arr.elems(elements);
    for (std::vector<mongo::BSONElement>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        mongo::BSONObj obj2 = it->Obj();
        _subPreguntas.append(Factory::crearPregunta(obj2, false));
    }
    _checked = o["checked"].Bool();
}
#else
PreguntaCompuesta::PreguntaCompuesta(QJsonObject &obj, bool showNotes, QObject *parent) : PreguntaBase(obj, showNotes, parent)
{
    QJsonObject o = obj["value"].toObject();
    QJsonArray arr = o["questions"].toArray();
    for (int i = 0; i < arr.count(); ++i)
    {
        QJsonObject obj2 = arr[i].toObject();
        _subPreguntas.append(Factory::crearPregunta(obj2, false));
    }
    _checked = o["checked"].toBool();
}
#endif

PreguntaCompuesta::~PreguntaCompuesta()
{

}

PreguntaBasePtr PreguntaCompuesta::clone()
{
    PreguntaCompuestaPtr p = PreguntaCompuestaPtr(new PreguntaCompuesta(label(), nota(), _subPreguntas, isShowingNotes(), parent()));
    return p;
}

QWidget* PreguntaCompuesta::widget()
{
    _widget = new WdgtCompuesto(isShowingNotes());
    _widget->setLabel(label());
    _widget->setChecked(_checked);
    _widget->setNotes(nota());
    foreach (PreguntaBasePtr preg, _subPreguntas)
    {
        _widget->addPregunta(preg);
    }
    return _widget;
}

#ifdef USEMONGO
mongo::BSONObj PreguntaCompuesta::value()
{
    mongo::BSONArrayBuilder builder;
    foreach (PreguntaBasePtr pregunta, _subPreguntas)
    {
        builder.append(pregunta->toBson());
    }
    mongo::BSONObj obj = BSON("questions" << builder.arr()
                              << "checked" << _checked);
    return obj;
}
#else
QJsonObject PreguntaCompuesta::value()
{
    QJsonArray builder;
    foreach (PreguntaBasePtr pregunta, _subPreguntas)
    {
        builder.append(pregunta->toJson());
    }
    QJsonObject obj;

    obj["questions"] = builder;
    obj["checked"] = _checked;

    return obj;
}
#endif

void PreguntaCompuesta::applyChanges()
{
    foreach (PreguntaBasePtr pregunta, _subPreguntas)
    {
        pregunta->applyChanges();
    }
    _checked = _widget->isChecked();
    setNota(_widget->notes());
}

QString PreguntaCompuesta::toHtml()
{
    return toHtml(true);
}

QString PreguntaCompuesta::toHtml(bool incluirNotas)
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";
    s += QString("<tr><td>%1</td><td>%2</td></tr>").arg(label()).arg(_checked ? "Si" : "No");
    foreach (PreguntaBasePtr pregunta, _subPreguntas)
    {
        s += QString("<tr><td colspan=\"2\">%1</td></tr>").arg(pregunta->toHtml(false));
    }
    if (incluirNotas)
        s += QString("<tr><td colspan=\"2\">%1</td></tr>").arg(nota());
    s += "</table>";
    return s;
}


QList<PreguntaBasePtr> PreguntaCompuesta::subPreguntas()
{
    return _subPreguntas;
}

bool PreguntaCompuesta::isChecked() const
{
    return _checked;
}
