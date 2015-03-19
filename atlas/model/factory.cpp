#include "factory.h"
#include "historiaclinica.h"
#include "persona.h"
#include "preguntabase.h"
#include "preguntacheckbox.h"
#include "preguntacombo.h"
#include "preguntacombodoble.h"
#include "preguntacompuesta.h"
#include "preguntasino.h"
#include "preguntatexto.h"
#include "alarma.h"

Factory::Factory(QObject *parent) : QObject(parent)
{
    cargarAntecedentes();
    cargarCuestionario();
}

Factory::~Factory()
{

}

HistoriaClinicaPtr Factory::crearNuevaHistoriaClinica()
{
    QList<PreguntaBasePtr> antecedentes = cloneAntecedentes();
    QList<PreguntaBasePtr> cuestionario = cloneCuestionario();

    HistoriaClinicaPtr hist = HistoriaClinicaPtr::create(crearPersona(), antecedentes, cuestionario);
    return hist;
}

HistoriaClinicaPtr Factory::crearHistoria(mongo::BSONObj &obj)
{
    HistoriaClinicaPtr hist = HistoriaClinicaPtr::create(obj);
    return hist;
}

PersonaPtr Factory::crearPersona()
{
    PersonaPtr persona = PersonaPtr::create();
    return persona;
}

QList<PreguntaBasePtr> Factory::cloneAntecedentes()
{
    QList<PreguntaBasePtr> ant;
    foreach (PreguntaBasePtr preg, _templateAntecedentes)
    {
        ant.append(preg->clone());
    }
    return ant;
}

QList<PreguntaBasePtr> Factory::cloneCuestionario()
{
    QList<PreguntaBasePtr> cuest;
    foreach (PreguntaBasePtr preg, _templateCuestionario)
    {
        cuest.append(preg->clone());
    }
    return cuest;
}

void Factory::cargarAntecedentes()
{
    _templateAntecedentes.clear();
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Cardiacos", "")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Neurologicos", "")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Respiratorios", "")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Renales", "")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Endocrinos", "")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Oncologicos", "")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Circulatorios", "")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Quirurgicos", "")));
    _templateAntecedentes.append(PreguntaComboPtr(new PreguntaCombo("Nacio por", "", QStringList() << "Parto Normal" << "Cesarea")));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Caidas, golpes intensos, accidentes, fracturas?", "")));
    _templateAntecedentes.append(PreguntaTextoPtr(new PreguntaTexto("Tratamiento Medico?", "")));
    _templateAntecedentes.append(PreguntaTextoPtr(new PreguntaTexto("Como ha estado animicamente", "")));
}

void Factory::cargarCuestionario()
{
    _templateCuestionario.clear();
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Cuello", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Espalda", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Hombro", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Codo", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Muñeca", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Manos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Lumbares", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Rodillas", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Pies", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Plantillas", ""))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Juanetes", "")))));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Hernia de disco", "",
                                                                                    QList<PreguntaBasePtr>()
                                                                                    << PreguntaCheckBoxPtr(new PreguntaCheckBox("Lumbar", ""))
                                                                                    << PreguntaCheckBoxPtr(new PreguntaCheckBox("Dorsal", ""))
                                                                                    << PreguntaCheckBoxPtr(new PreguntaCheckBox("Cervical", "")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Espalda", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Escoliosis", ""))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Lordosis", ""))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Cifosis", "")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Achaques", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Artrosis", ""))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Fibromalgia", ""))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Esclerosis múltiple", "")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Dolor de cabeza", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierda", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecha", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Mandíbula", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierda", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecha", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Oídos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierda", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecha", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Mareos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierda", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo"))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecha", "", QStringList() << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "Ocasional" << "Frecuente" << "Continuo")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Desvanecimientos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboPtr(new PreguntaCombo("Desmayos", "", QStringList() << "Nunca" << "Ocasional" << "Frecuente")))));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Descanso", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaSiNoPtr(new PreguntaSiNo("Cansancio en el día?", ""))
                                                                            << PreguntaSiNoPtr(new PreguntaSiNo("Le cuesta dormir?", ""))
                                                                            << PreguntaSiNoPtr(new PreguntaSiNo("Sueño liviano?", ""))
                                                                            << PreguntaComboPtr(new PreguntaCombo("Se levanta", "", QStringList() << "Cansado" << "Descansado")))));
}

PreguntaBasePtr Factory::crearPregunta(mongo::BSONObj &obj)
{
    QString type = obj["type"].String().c_str();
    PreguntaBasePtr preg;
    if (type == "checkbox")
    {
        preg = PreguntaCheckBoxPtr(new PreguntaCheckBox(obj));
    }
    else if (type == "combo")
    {
        preg = PreguntaComboPtr(new PreguntaCombo(obj));
    }
    else if (type == "combodoble")
    {
        preg = PreguntaComboDoblePtr(new PreguntaComboDoble(obj));
    }
    else if (type == "compuesta")
    {
        preg = PreguntaCompuestaPtr(new PreguntaCompuesta(obj));
    }
    else if (type == "yesno")
    {
        preg = PreguntaSiNoPtr(new PreguntaSiNo(obj));
    }
    else if (type == "text")
    {
        preg = PreguntaTextoPtr(new PreguntaTexto(obj));
    }
    return preg;
}

AlarmaPtr Factory::crearAlarma(mongo::BSONObj &obj)
{
    return AlarmaPtr(new Alarma(obj));
}

AlarmaPtr Factory::crearNuevaAlarma(HistoriaClinicaPtr historia)
{
    return AlarmaPtr(new Alarma(historia));
}
