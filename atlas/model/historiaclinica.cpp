#include "historiaclinica.h"
#include "persona.h"
#include "preguntabase.h"
#include <mongo/bson/bsonelement.h>
#include "persona.h"
#include "factory.h"

HistoriaClinica::HistoriaClinica(PersonaPtr persona,
                                 QList<PreguntaBasePtr> &templateAntecedentes,
                                 QList<PreguntaBasePtr> &templateTestKinesiologico,
                                 QList<PreguntaBasePtr> &templateCuestionario1erConsulta,
                                 QList<PreguntaBasePtr> &templateCuestionario2daConsulta,
                                 QObject *parent) : QObject(parent)
{
    _persona = persona;
    _antecedentes = templateAntecedentes;
    _testKinesiologico = templateTestKinesiologico;
    _cuestionario1erConsulta = templateCuestionario1erConsulta;
    _cuestionario2daConsulta = templateCuestionario2daConsulta;
    _fechaPrimerConsulta = QDate();
    _fechaSegundaConsulta = QDate();
    _numeroPaciente = "-1";
}

HistoriaClinica::HistoriaClinica(mongo::BSONObj &obj, QObject *parent) : QObject(parent)
{
    //qDebug() << QString(obj.jsonString().c_str());
    mongo::BSONObj p = obj["persona"].Obj();
    _persona = PersonaPtr(new Persona(p));

    long fecha = obj["FechaPrimerConsulta"].Long();
    _fechaPrimerConsulta = (fecha == -1) ? QDate() : QDate::fromJulianDay(fecha);
    fecha = obj["FechaSegundaConsulta"].Long();
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
        fromArrayBson(elements, _testKinesiologico);
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

QList<PreguntaBasePtr>& HistoriaClinica::testKinesiologico()
{
    return _testKinesiologico;
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


mongo::BSONObj HistoriaClinica::toBson()
{
    mongo::BSONObj obj =
            BSON( "persona" << _persona->toBson()
                  << "FechaPrimerConsulta" << (_fechaPrimerConsulta.isValid() ?  _fechaPrimerConsulta.toJulianDay() : -1)
                  << "FechaSegundaConsulta" << (_fechaSegundaConsulta.isValid() ? _fechaSegundaConsulta.toJulianDay() : -1)
                  << "antecedentes" << arrayBson(_antecedentes)
                  << "testKinesiologico" << arrayBson(_testKinesiologico)
                  << "cuestionario1erConsulta" << arrayBson(_cuestionario1erConsulta)
                  << "cuestionario2daConsulta" << arrayBson(_cuestionario2daConsulta)
                  << "numeroPaciente" << _numeroPaciente.toStdString());
    return obj;
}

mongo::BSONObj HistoriaClinica::arrayBson(QList<PreguntaBasePtr> list)
{
    mongo::BSONArrayBuilder builder;
    foreach (PreguntaBasePtr pregunta, list)
    {
        builder.append(pregunta->toBson());
    }
    return builder.arr();
}

void HistoriaClinica::fromArrayBson(std::vector<mongo::BSONElement> &arr, QList<PreguntaBasePtr> &list)
{
    list.clear();
    //qDebug() << arr.size();
    for(uint i = 0; i < arr.size(); ++i)
    {
        mongo::BSONObj obj = arr[i].Obj();
        //qDebug() << obj.jsonString().c_str();
        list.append(Factory::crearPregunta(obj, true));
    }
}

QString HistoriaClinica::idString()
{
    return QString(_id.toString().c_str());
}

mongo::OID HistoriaClinica::id()
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
    s += QString("<tr><td colspan=\"3\">%1</td></tr>").arg(html(_testKinesiologico, 3));
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
