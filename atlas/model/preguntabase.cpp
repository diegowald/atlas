#include "preguntabase.h"
#include "../widgets/wdgtwithlabel.h"

PreguntaBase::PreguntaBase(const QString &label, const QString &nota, const QString &type, bool showNotes, QObject *parent) : QObject(parent)
{
    _label = label;
    _nota = nota;
    _type = type;
    _showNotes = showNotes;
}

#ifdef USEMONGO
PreguntaBase::PreguntaBase(mongo::BSONObj &obj, bool showNotes, QObject *parent)
{
    _label = obj["label"].String().c_str();
    _nota = obj["nota"].String().c_str();
    _type = obj["type"].String().c_str();
    _showNotes = showNotes;
}
#else
PreguntaBase::PreguntaBase(QJsonObject &obj, bool showNotes, QObject *parent)
{
    _label = obj["label"].toString();
    _nota = obj["nota"].toString();
    _type = obj["type"].toString();
    _showNotes = showNotes;
}
#endif

PreguntaBase::~PreguntaBase()
{

}

void PreguntaBase::setLabel(const QString &Label)
{
    _label = Label;
}

void PreguntaBase::setNota(const QString &Nota)
{
    _nota = Nota;
}

QString PreguntaBase::label() const
{
    return _label;
}

QString PreguntaBase::nota() const
{
    return _nota;
}

QWidget *PreguntaBase::widget(bool includeLabel)
{
    return includeLabel ? widgetWithLabel() : widget();
}

QWidget *PreguntaBase::widgetWithLabel()
{
    WdgtWithLabel *wdget = new WdgtWithLabel(isShowingNotes());
    wdget->addWidget(_label, widget());
    return wdget;
}

#ifdef USEMONGO
mongo::BSONObj PreguntaBase::toBson()
{
    mongo::BSONObj obj = BSON(
                "label" << _label.toStdString()
                << "nota" << _nota.toStdString()
                << "type" << _type.toStdString()
                << "value" << value());
    return obj;
}
#else
QJsonObject PreguntaBase::toJson()
{
    QJsonObject obj;

    obj["label"] = _label;
    obj["nota"] = _nota;
    obj["type"] = _type;
    obj["value"] = value();
    return obj;
}
#endif

bool PreguntaBase::isShowingNotes() const
{
    return _showNotes;
}
