#include "historiaclinica.h"
#include "persona.h"
#include "preguntabase.h"

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
                  /*<< "cuestionario" << _cuestionario.toBson()*/
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
