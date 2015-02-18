#include "preguntacompuesta.h"
#include <QDebug>
#include "factory.h"

PreguntaCompuesta::PreguntaCompuesta(const QString &label, const QString &nota, QList<PreguntaBasePtr> &subpreguntas, QObject *parent) : PreguntaBase(label, nota, "compuesta", parent)
{
    foreach (PreguntaBasePtr pb, subpreguntas)
    {
        _subPreguntas.append(pb->clone());
    }
    _checked = true;
}

PreguntaCompuesta::PreguntaCompuesta(mongo::BSONObj &obj, QObject *parent) : PreguntaBase(obj, parent)
{
    mongo::BSONObj o = obj["value"].Obj();
    mongo::BSONObj arr = o["questions"].Obj();
    std::vector<mongo::BSONElement> elements;
    arr.elems(elements);
    for (std::vector<mongo::BSONElement>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        mongo::BSONObj obj2 = it->Obj();
        qDebug() << obj2.jsonString().c_str();
        _subPreguntas.append(Factory::crearPregunta(obj2));
    }
    _checked = o["checked"].Bool();
}

PreguntaCompuesta::~PreguntaCompuesta()
{

}

PreguntaBasePtr PreguntaCompuesta::clone()
{
    PreguntaCompuestaPtr p = PreguntaCompuestaPtr(new PreguntaCompuesta(label(), nota(), _subPreguntas, parent()));
    return p;
}

QWidget* PreguntaCompuesta::widget()
{
    _widget = new WdgtCompuesto();
    _widget->setLabel(label());
    _widget->setChecked(_checked);
    foreach (PreguntaBasePtr preg, _subPreguntas)
    {
        _widget->addPregunta(preg);
    }
    return _widget;
}

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

void PreguntaCompuesta::applyChanges()
{
    foreach (PreguntaBasePtr pregunta, _subPreguntas)
    {
        pregunta->applyChanges();
    }
    _checked = _widget->isChecked();
}
