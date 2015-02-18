#include "historiaclinica.h"
#include "persona.h"
#include "preguntabase.h"
#include <QDebug>
#include <mongo/bson/bsonelement.h>
#include "persona.h"
#include "factory.h"

HistoriaClinica::HistoriaClinica(PersonaPtr persona,
                                 QList<PreguntaBasePtr> &templateAntecedentes,
                                 QList<PreguntaBasePtr> &templateCuestionario,
                                 QObject *parent) : QObject(parent)
{
    _persona = persona;
    _antecedentes = templateAntecedentes;
    _cuestionario = templateCuestionario;
    _fechaPrimerConsulta = QDate(0, 0, 0);
    _fechaSegundaConsulta = QDate(0, 0, 0);
    _numeroPaciente = "-1";
}

HistoriaClinica::HistoriaClinica(mongo::BSONObj &obj, QObject *parent) : QObject(parent)
{
    qDebug() << QString(obj.jsonString().c_str());
    mongo::BSONObj p = obj["persona"].Obj();
    _persona = PersonaPtr::create(p);
    _fechaPrimerConsulta = QDate::fromString(QString(obj["FechaPrimerConsulta"].String().c_str()));
    _fechaSegundaConsulta = QDate::fromString(QString(obj["FechaSegundaConsulta"].String().c_str()));
    mongo::BSONObj arr = obj["antecedentes"].Obj();
    std::vector<mongo::BSONElement> elements;
    arr.elems(elements);
    fromArrayBson(elements, _antecedentes);
    arr = obj["cuestionario"].Obj();
    elements.clear();
    arr.elems(elements);
    fromArrayBson(elements, _cuestionario);
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

QList<PreguntaBasePtr> &HistoriaClinica::cuestionario()
{
    return _cuestionario;
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
                  << "FechaPrimerConsulta" << _fechaPrimerConsulta.toString().toStdString()
                  << "FechaSegundaConsulta" << _fechaSegundaConsulta.toString().toStdString()
                  << "antecedentes" << arrayBson(_antecedentes)
                  << "cuestionario" << arrayBson(_cuestionario)
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
    qDebug() << arr.size();
    for(uint i = 0; i < arr.size(); ++i)
    {
        mongo::BSONObj obj = arr[i].Obj();
        qDebug() << obj.jsonString().c_str();
        list.append(Factory::crearPregunta(obj));
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
