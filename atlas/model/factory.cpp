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

// Reporting
#include "../reporting/reportebase.h"
#include "../reporting/reportepreguntacheckbox.h"
#include "../reporting/reportepreguntacombo.h"
#include "../reporting/reportepreguntacombodoble.h"
#include "../reporting/reportepreguntacompuesta.h"
#include "../reporting/reportepreguntasino.h"
#include "../reporting/reportepreguntatexto.h"

Factory::Factory(QObject *parent) : QObject(parent)
{
    cargarAntecedentes();
    cargarTestKinesiologico();
    cargarCuestionario();
}

Factory::~Factory()
{

}

HistoriaClinicaPtr Factory::crearNuevaHistoriaClinica()
{
    QList<PreguntaBasePtr> antecedentes = cloneAntecedentes();
    QList<PreguntaBasePtr> testKinesiologico1erConsulta = cloneTestKinesiologico();
    QList<PreguntaBasePtr> testKinesiologico2daConsulta = cloneTestKinesiologico();
    testKinesiologico2daConsulta.clear();
    QList<PreguntaBasePtr> cuestionario1erConsulta = cloneCuestionario();
    QList<PreguntaBasePtr> cuestionario2daConsulta = cloneCuestionario();

    HistoriaClinicaPtr hist = HistoriaClinicaPtr(
                new HistoriaClinica(crearPersona(),
                                    antecedentes,
                                    testKinesiologico1erConsulta,
                                    testKinesiologico2daConsulta,
                                    cuestionario1erConsulta,
                                    cuestionario2daConsulta));
    return hist;
}

#ifdef USEMONGO
HistoriaClinicaPtr Factory::crearHistoria(mongo::BSONObj &obj)
#else
HistoriaClinicaPtr Factory::crearHistoria(QJsonObject &obj)
#endif
{
    HistoriaClinicaPtr hist = HistoriaClinicaPtr(new HistoriaClinica(obj));
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

QList<PreguntaBasePtr> Factory::cloneTestKinesiologico()
{
    QList<PreguntaBasePtr> t;
    foreach (PreguntaBasePtr preg, _templateTestKinesiologico)
    {
        t.append(preg->clone());
    }
    return t;
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
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Cardiacos", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Neurologicos", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Respiratorios", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Digestivos", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Renales", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Endocrinos", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Oncologicos", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Circulatorios", "", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Quirurgicos", "", true)));
    _templateAntecedentes.append(PreguntaComboPtr(new PreguntaCombo("Nacio por", "", QStringList() << "" << "Parto Normal" << "Cesarea", true)));
    _templateAntecedentes.append(PreguntaCheckBoxPtr(new PreguntaCheckBox("Caidas, golpes intensos, accidentes, fracturas?", "", true)));
    _templateAntecedentes.append(PreguntaTextoPtr(new PreguntaTexto("Tratamiento Medico?", "", true)));
    _templateAntecedentes.append(PreguntaTextoPtr(new PreguntaTexto("Como ha estado animicamente", "", true)));
}

void Factory::cargarTestKinesiologico()
{
    _templateTestKinesiologico.clear();
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Test PCF ext. A", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Test PCF flex. A", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Dolor cadera/pierna", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("ECM. Tensión", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("ECM. Oblicuidad", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Mastoides-Mandib.", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Tono musc. subocc.", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Dolor Movil. Cuello", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Restricción Mov.", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Línea Mordida oclusión", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Línea Mordida apert.", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Brazo Corto F. Ext.", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("brazo Corto F. Elev.", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Elev. Hombros", "", true)));
    _templateTestKinesiologico.append(PreguntaTextoPtr(new PreguntaTexto("Postura", "", true)));
}

void Factory::cargarCuestionario()
{
    _templateCuestionario.clear();
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Cuello", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Espalda", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Hombro", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Brazo", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Codo", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Muñeca", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Manos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Lumbares", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Ciático", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Cadera", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Piernas", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Rodillas", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Pies", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierdo", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecho", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Plantillas", "", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Juanete Izq.", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Juanete Der.", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)),  true)));

                                                                                                    //, true)));
                                                                                //<< PreguntaCheckBoxPtr(new PreguntaCheckBox("Juanetes", "", false)), true)));
    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Hernia de disco", "",
                                                                                    QList<PreguntaBasePtr>()
                                                                                    << PreguntaCheckBoxPtr(new PreguntaCheckBox("Lumbar", "", false))
                                                                                    << PreguntaCheckBoxPtr(new PreguntaCheckBox("Dorsal", "", false))
                                                                                    << PreguntaCheckBoxPtr(new PreguntaCheckBox("Cervical", "", false)), true)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Espalda", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Escoliosis", "", false))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Lordosis", "", false))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Cifosis", "", false)), true)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Otros", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Artrosis", "", false))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Fibromalgia", "", false))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Esclerosis múltiple", "", false)), true)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Dolor de cabeza", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierda", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecha", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false)), true)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Mandíbula", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Dolor", "", false))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Mala oclusión", "", false))
                                                                            << PreguntaCheckBoxPtr(new PreguntaCheckBox("Bruxismo", "", false)), true)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Oídos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            /*<< PreguntaComboDoblePtr(new PreguntaComboDoble("Izquierda", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Derecha", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))*/
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Zumbidos Izq", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Zumbidos Der", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))
                                                                            /*<< PreguntaComboDoblePtr(new PreguntaComboDoble("Puntadas", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", false))*/, true)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Mareos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboDoblePtr(new PreguntaComboDoble("Mareos", "", QStringList() << "" << "Sin dolor" << "Leve" << "Moderado" << "Intenso", QStringList() << "" << "Ocasional" << "Frecuente" << "Continuo", true)), false)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Desvanecimientos", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaComboPtr(new PreguntaCombo("Desmayos", "", QStringList() << "" << "Nunca" << "Ocasional" << "Frecuente", true)), false)));

    _templateCuestionario.append(PreguntaCompuestaPtr(new PreguntaCompuesta("Descanso", "",
                                                                            QList<PreguntaBasePtr>()
                                                                            << PreguntaSiNoPtr(new PreguntaSiNo("Cansancio en el día?", "", false))
                                                                            << PreguntaSiNoPtr(new PreguntaSiNo("Le cuesta dormir?", "", false))
                                                                            << PreguntaSiNoPtr(new PreguntaSiNo("Sueño liviano?", "", false))
                                                                            << PreguntaComboPtr(new PreguntaCombo("Se levanta", "", QStringList() << "" << "Cansado" << "Descansado", false)), true)));
}

#ifdef USEMONGO
PreguntaBasePtr Factory::crearPregunta(mongo::BSONObj &obj, bool showNotes)
#else
PreguntaBasePtr Factory::crearPregunta(QJsonObject &obj, bool showNotes)
#endif
{
#ifdef USEMONGO
    QString type = obj["type"].String().c_str();
#else
    QString type = obj["type"].toString();
#endif
    PreguntaBasePtr preg;
    if (type == "checkbox")
    {
        preg = PreguntaCheckBoxPtr(new PreguntaCheckBox(obj, showNotes));
    }
    else if (type == "combo")
    {
        preg = PreguntaComboPtr(new PreguntaCombo(obj, showNotes));
    }
    else if (type == "combodoble")
    {
        preg = PreguntaComboDoblePtr(new PreguntaComboDoble(obj, showNotes));
    }
    else if (type == "compuesta")
    {
        preg = PreguntaCompuestaPtr(new PreguntaCompuesta(obj, showNotes));
    }
    else if (type == "yesno")
    {
        preg = PreguntaSiNoPtr(new PreguntaSiNo(obj, showNotes));
    }
    else if (type == "text")
    {
        preg = PreguntaTextoPtr(new PreguntaTexto(obj, showNotes));
    }
    return preg;
}

ReporteBasePtr Factory::crearDatoReporte(PreguntaBasePtr pregunta)
{
    QString type = pregunta->type();
    ReporteBasePtr rpt;
    if (type == "checkbox")
    {
        rpt = ReportePreguntaCheckBoxPtr(new ReportePreguntaCheckBox(qSharedPointerDynamicCast<PreguntaCheckBox>(pregunta)));
    }
    else if (type == "combo")
    {
        rpt = ReportePreguntaComboPtr(new ReportePreguntaCombo(qSharedPointerDynamicCast<PreguntaCombo>(pregunta)));
    }
    else if (type == "combodoble")
    {
        rpt = ReportePreguntaComboDoblePtr(new ReportePreguntaComboDoble(qSharedPointerDynamicCast<PreguntaComboDoble>(pregunta)));
    }
    else if (type == "compuesta")
    {
        rpt = ReportePreguntaCompuestaPtr(new ReportePreguntaCompuesta(qSharedPointerDynamicCast<PreguntaCompuesta>(pregunta)));
    }
    else if (type == "yesno")
    {
        rpt = ReportePreguntaSiNoPtr(new ReportePreguntaSiNo(qSharedPointerDynamicCast<PreguntaSiNo>(pregunta)));
    }
    else if (type == "text")
    {
        rpt = ReportePreguntaTextoPtr(new ReportePreguntaTexto(qSharedPointerDynamicCast<PreguntaTexto>(pregunta)));
    }
    return rpt;
}

#ifdef USEMONGO
AlarmaPtr Factory::crearAlarma(mongo::BSONObj &obj)
#else
AlarmaPtr Factory::crearAlarma(QJsonObject &obj)
#endif
{
    return AlarmaPtr(new Alarma(obj));
}

AlarmaPtr Factory::crearNuevaAlarma(HistoriaClinicaPtr historia)
{
    return AlarmaPtr(new Alarma(historia));
}

