#include "historiaclinica.h"

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
