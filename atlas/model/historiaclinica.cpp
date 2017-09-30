#include "historiaclinica.h"
#include "persona.h"
#include "preguntabase.h"
#ifdef USEMONGO
#include <mongo/bson/bsonelement.h>
#else
#include <QJsonArray>
#endif
#include "persona.h"
#include "factory.h"
#include <QDebug>
#include <QUuid>

HistoriaClinica::HistoriaClinica(PersonaPtr persona,
                                 QList<PreguntaBasePtr> &templateAntecedentes,
                                 QList<PreguntaBasePtr> &templateTestKinesiologico1erConsulta,
                                 QList<PreguntaBasePtr> &templateTestKinesiologico2daConsulta,
                                 QList<PreguntaBasePtr> &templateCuestionario1erConsulta,
                                 QList<PreguntaBasePtr> &templateCuestionario2daConsulta,
                                 QObject *parent) : QObject(parent)
{
    _persona = persona;
    _antecedentes = templateAntecedentes;
    _testKinesiologico1erConsulta = templateTestKinesiologico1erConsulta;
    _testKinesiologico2daConsulta = templateTestKinesiologico2daConsulta;
    _cuestionario1erConsulta = templateCuestionario1erConsulta;
    _cuestionario2daConsulta = templateCuestionario2daConsulta;
    _fechaPrimerConsulta = QDate();
    _fechaSegundaConsulta = QDate();
    _numeroPaciente = "-1";
    QUuid uuid = QUuid::createUuid();
    _id = uuid.toString();
}

#ifdef USEMONGO
HistoriaClinica::HistoriaClinica(mongo::BSONObj &obj, QObject *parent) : QObject(parent)
{
    mongo::BSONObj p = obj["persona"].Obj();
    _persona = PersonaPtr(new Persona(p));

    mongo::BSONType t = obj["FechaPrimerConsulta"].type();

    long fecha = -1;
    switch(t)
    {
        case mongo::NumberInt:
            fecha = (long) obj["FechaPrimerConsulta"].Int();
            break;
        case mongo::NumberDouble:
            fecha = (long) obj["FechaPrimerConsulta"].Double();
            break;
        case mongo::NumberLong:
            fecha = obj["FechaPrimerConsulta"].Long();
            break;
        default:
            break;
    }

    _fechaPrimerConsulta = (fecha == -1) ? QDate() : QDate::fromJulianDay(fecha);

    t = obj["FechaSegundaConsulta"].type();
    switch(t)
    {
        case mongo::NumberInt:
            fecha = (long) obj["FechaSegundaConsulta"].Int();
            break;
        case mongo::NumberDouble:
            fecha = (long) obj["FechaSegundaConsulta"].Double();
            break;
        case mongo::NumberLong:
            fecha = obj["FechaSegundaConsulta"].Long();
            break;
        default:
            break;
    }
    _fechaSegundaConsulta = (fecha == -1) ? QDate() : QDate::fromJulianDay(fecha);

    mongo::BSONObj arr = obj["antecedentes"].Obj();
    std::vector<mongo::BSONElement> elements;
    arr.elems(elements);
    fromArrayBson(elements, _antecedentes);

    if (obj.hasField("testKinesiologico"))
    {
        arr = obj["testKinesiologico"].Obj();
        elements.clear();
        arr.elems(elements);
        fromArrayBson(elements, _testKinesiologico1erConsulta);
    }

    if (obj.hasField("testKinesiologico2daConsulta"))
    {
        arr = obj["testKinesiologico2daConsulta"].Obj();
        elements.clear();
        arr.elems(elements);
        fromArrayBson(elements, _testKinesiologico2daConsulta);
    }

    arr = obj["cuestionario1erConsulta"].Obj();
    elements.clear();
    arr.elems(elements);
    fromArrayBson(elements, _cuestionario1erConsulta);

    arr = obj["cuestionario2daConsulta"].Obj();
    elements.clear();
    arr.elems(elements);
    fromArrayBson(elements, _cuestionario2daConsulta);

    _numeroPaciente = obj["numeroPaciente"].String().c_str();
    _id = obj["_id"].OID();
}
#else
HistoriaClinica::HistoriaClinica(QJsonObject &obj, QObject *parent) : QObject(parent)
{
    QJsonObject p = obj["persona"].toObject();
    _persona = PersonaPtr(new Persona(p));


    long fecha = obj["FechaPrimerConsulta"].toInt();
    _fechaPrimerConsulta = (fecha == -1) ? QDate() : QDate::fromJulianDay(fecha);

    fecha = obj["FechaSegundaConsulta"].toInt();
    _fechaSegundaConsulta = (fecha == -1) ? QDate() : QDate::fromJulianDay(fecha);

    QJsonValue v = obj["antecedentes"];
    fromArrayJson(v, _antecedentes);

    if (obj.contains("testKinesiologico"))
    {
        v = obj["testKinesiologico"];
        fromArrayJson(v, _testKinesiologico1erConsulta);
    }

    if (obj.contains("testKinesiologico2daConsulta"))
    {
        v = obj["testKinesiologico2daConsulta"];
        fromArrayJson(v, _testKinesiologico2daConsulta);
    }

    v = obj["cuestionario1erConsulta"];
    fromArrayJson(v, _cuestionario1erConsulta);

    v = obj["cuestionario2daConsulta"];
    fromArrayJson(v, _cuestionario2daConsulta);

    _numeroPaciente = obj["numeroPaciente"].toString();
    _id = obj["_id"].toObject()["$oid"].toString();
    if (_id.length() == 0)
        _id = obj["id"].toString();
}
#endif

HistoriaClinica::~HistoriaClinica()
{

}

PersonaPtr HistoriaClinica::persona()
{
    return _persona;
}

QDate HistoriaClinica::fechaPrimerConsulta()
{
    return _fechaPrimerConsulta;
}

QDate HistoriaClinica::fechaSegundaConsulta()
{
    return _fechaSegundaConsulta;
}

QString HistoriaClinica::numeroPaciente()
{
    return _numeroPaciente;
}

QList<PreguntaBasePtr>& HistoriaClinica::antecedentes()
{
    return _antecedentes;
}

QList<PreguntaBasePtr>& HistoriaClinica::testKinesiologico1erConsulta()
{
    return _testKinesiologico1erConsulta;
}

QList<PreguntaBasePtr> &HistoriaClinica::testKinesiologico2darConsulta()
{
    return _testKinesiologico2daConsulta;
}

QList<PreguntaBasePtr> &HistoriaClinica::cuestionario1erConsulta()
{
    return _cuestionario1erConsulta;
}

QList<PreguntaBasePtr> &HistoriaClinica::cuestionario2daConsulta()
{
    return _cuestionario2daConsulta;
}

void HistoriaClinica::setFechaPrimerConsulta(QDate &date)
{
    _fechaPrimerConsulta = date;
}

void HistoriaClinica::setFechaSegundaConsulta(QDate &date)
{
    _fechaSegundaConsulta = date;
}

void HistoriaClinica::setNumeroPaciente(const QString &nro)
{
    _numeroPaciente = nro;
}

#ifdef USEMONGO
mongo::BSONObj HistoriaClinica::toBson()
{
    mongo::BSONObj obj =
            BSON( "persona" << _persona->toBson()
                  << "FechaPrimerConsulta" << (_fechaPrimerConsulta.isValid() ?  _fechaPrimerConsulta.toJulianDay() : -1)
                  << "FechaSegundaConsulta" << (_fechaSegundaConsulta.isValid() ? _fechaSegundaConsulta.toJulianDay() : -1)
                  << "antecedentes" << arrayBson(_antecedentes)
                  << "testKinesiologico" << arrayBson(_testKinesiologico1erConsulta)
                  << "testKinesiologico2daConsulta" << arrayBson(_testKinesiologico2daConsulta)
                  << "cuestionario1erConsulta" << arrayBson(_cuestionario1erConsulta)
                  << "cuestionario2daConsulta" << arrayBson(_cuestionario2daConsulta)
                  << "numeroPaciente" << _numeroPaciente.toStdString());
    return obj;
}
#else
QJsonObject HistoriaClinica::toJson()
{
    QJsonObject obj;
    obj["id"] = _id;
    obj["persona"] = _persona->toJson();
    obj["FechaPrimerConsulta"] = (_fechaPrimerConsulta.isValid() ?  _fechaPrimerConsulta.toJulianDay() : -1);
    obj["FechaSegundaConsulta"] = (_fechaSegundaConsulta.isValid() ? _fechaSegundaConsulta.toJulianDay() : -1);
    obj["antecedentes"] = arrayJson(_antecedentes);
    obj["testKinesiologico"] = arrayJson(_testKinesiologico1erConsulta);
    obj["testKinesiologico2daConsulta"] = arrayJson(_testKinesiologico2daConsulta);
    obj["cuestionario1erConsulta"] = arrayJson(_cuestionario1erConsulta);
    obj["cuestionario2daConsulta"] = arrayJson(_cuestionario2daConsulta);
    obj["numeroPaciente"] = _numeroPaciente;
    return obj;
}
#endif

#ifdef USEMONGO
mongo::BSONObj HistoriaClinica::arrayBson(QList<PreguntaBasePtr> list)
{
    mongo::BSONArrayBuilder builder;
    foreach (PreguntaBasePtr pregunta, list)
    {
        builder.append(pregunta->toBson());
    }
    return builder.arr();
}
#else
QJsonArray HistoriaClinica::arrayJson(QList<PreguntaBasePtr> list)
{
    QJsonArray builder;
    foreach (PreguntaBasePtr pregunta, list)
    {
        builder.append(pregunta->toJson());
    }
    return builder;
}
#endif

#ifdef USEMONGO
void HistoriaClinica::fromArrayBson(std::vector<mongo::BSONElement> &arr, QList<PreguntaBasePtr> &list)
{
    list.clear();
    for(uint i = 0; i < arr.size(); ++i)
    {
        mongo::BSONObj obj = arr[i].Obj();
        list.append(Factory::crearPregunta(obj, true));
    }
}
#else
void HistoriaClinica::fromQJsonArray(QJsonArray &arr, QList<PreguntaBasePtr> &list)
{
    list.clear();
    for(uint i = 0; i < arr.size(); ++i)
    {
        QJsonObject obj = arr[i].toObject();
        list.append(Factory::crearPregunta(obj, true));
    }
}

void HistoriaClinica::fromQObjectArray(QJsonObject &arr, QList<PreguntaBasePtr> &list)
{
    foreach(QString key, arr.keys())
    {
        QJsonObject obj = arr.value(key).toObject();
        list.append(Factory::crearPregunta(obj, true));
    }
}

void HistoriaClinica::fromArrayJson(QJsonValue &arr, QList<PreguntaBasePtr> &list)
{
    if (arr.isArray())
    {
        QJsonArray arr2 = arr.toArray();
        fromQJsonArray(arr2, list);
    }
    else if (arr.isObject())
    {
        QJsonObject arr2 = arr.toObject();
        fromQObjectArray(arr2, list);
    }
}
#endif

QString HistoriaClinica::idString()
{
#ifdef USEMONGO
    return _id.toString().c_str());
#else
    return _id;
#endif
}

#ifdef USEMONGO
mongo::OID HistoriaClinica::id()
#else
QString HistoriaClinica::id()
#endif
{
    return _id;
}

QString HistoriaClinica::toHtml()
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";

    s += "<tr>";
    s += QString("<td>Primer Consulta : %1</td><td>Segunda Consulta: %2</td><td># %3</td>")
            .arg(_fechaPrimerConsulta.toString("dd/MM/yyyy"))
            .arg(_fechaSegundaConsulta.toString("dd/MM/yyyy"))
            .arg(_numeroPaciente);
    s += "</tr>";
    s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(_persona->toHtml());
    s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(html(_antecedentes, 3));
    s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(html(_testKinesiologico1erConsulta, 3));
    s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(html(_testKinesiologico2daConsulta, 3));
    s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(html(_cuestionario1erConsulta, 3));
    s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(html(_cuestionario2daConsulta, 3));

    s += "</table>";

    return s;
}

QString HistoriaClinica::html(QList<PreguntaBasePtr> &lista, int cantColumnas)
{
    QString s = "<table width=\"100%\" style=\"border:1px solid black;\">";

    int columna = 1;
    foreach (PreguntaBasePtr pregunta, lista)
    {
        if (columna == 1)
        {
            s += "<tr>";
        }
        s += QString("<td>%1</td>").arg(pregunta->toHtml());
        if (columna == cantColumnas)
        {
            s += "</tr>";
            columna = 0;
        }
        columna++;
    }
    if (!s.endsWith("</tr>"))
    {
        s += "</tr>";
    }

    s += "</table>";
    return s;
}
