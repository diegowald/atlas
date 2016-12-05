#include "reports.h"
#ifdef USEMONGO
#include "../db/dbmanager.h"
#else
#include "../db/dbrestmanaget.h"
#endif
#include <QDate>
#include <QMap>
#include "../model/factory.h"
#include "../model/forward.h"
#include "../model/historiaclinica.h"
#include "../model/preguntabase.h"
#include "reportebase.h"

Reports::Reports(QObject *parent) : QObject(parent)
{
#ifndef USEMONGO
    connect(DBRestManager::instance(), &DBRestManager::historiasReturned, this, &Reports::on_historiasReturned);
#endif
}

Reports::~Reports()
{
}

#ifdef USEMONGO
QDialog *Reports::runContabilizacionPatologiasEntreFechas(QDate &dateFrom, QDate &dateTo, bool filterOn1stAppt, QWidget *parent)
{
    QString queryPattern = "{%1: { $gt: %2, $lt: %3 } }";
    QString query = queryPattern
            .arg(filterOn1stAppt ? "FechaPrimerConsulta" : "FechaSegundaConsulta")
            .arg(dateFrom.toJulianDay())
            .arg(dateTo.toJulianDay());

    QMap<QString, HistoriaClinicaPtr> historias = dbManager::instance()->historias(query);

    QMap<QString, ReporteBasePtr> datosReporte;

    foreach(HistoriaClinicaPtr historia, historias)
    {
        QList<PreguntaBasePtr> cuestionario = filterOn1stAppt ?
                    historia->cuestionario1erConsulta() :
                    historia->cuestionario2daConsulta();
        foreach(PreguntaBasePtr pregunta, cuestionario)
        {
            if (!datosReporte.contains(pregunta->label()))
            {
                datosReporte[pregunta->label()] = Factory::crearDatoReporte(pregunta);
            }
            else
            {
                datosReporte[pregunta->label()]->add(pregunta);
            }
        }
    }
    QString html = buildReportContabilizacionPatologiasEntreFechas(dateFrom, dateTo, filterOn1stAppt, datosReporte, historias.count());
    DlgReporte* dlg = new DlgReporte();
    dlg->setReportData(html);
    return dlg;
}
#else
QDialog *Reports::runContabilizacionPatologiasEntreFechas(QDate &dateFrom, QDate &dateTo, bool filterOn1stAppt, QWidget *parent)
{
    QString queryPattern = "{%1: { $gt: %2, $lt: %3 } }";
    QString query = queryPattern
            .arg(filterOn1stAppt ? "FechaPrimerConsulta" : "FechaSegundaConsulta")
            .arg(dateFrom.toJulianDay())
            .arg(dateTo.toJulianDay());

    _dateFrom = dateFrom;
    _dateTo = dateTo;
    _filterOn1stAppt = filterOn1stAppt;

    DBRestManager::instance()->historias(query);

    _dlg = new DlgReporte();
    return _dlg;
}

void Reports::on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias)
{
    QMap<QString, ReporteBasePtr> datosReporte;

    foreach(HistoriaClinicaPtr historia, historias)
    {
        QList<PreguntaBasePtr> cuestionario = _filterOn1stAppt ?
                    historia->cuestionario1erConsulta() :
                    historia->cuestionario2daConsulta();
        foreach(PreguntaBasePtr pregunta, cuestionario)
        {
            if (!datosReporte.contains(pregunta->label()))
            {
                datosReporte[pregunta->label()] = Factory::crearDatoReporte(pregunta);
            }
            else
            {
                datosReporte[pregunta->label()]->add(pregunta);
            }
        }
    }
    QString html = buildReportContabilizacionPatologiasEntreFechas(_dateFrom, _dateTo, _filterOn1stAppt, datosReporte, historias.count());
    _dlg->setReportData(html);
}
#endif


QString Reports::buildReportContabilizacionPatologiasEntreFechas(QDate &dateFrom,
                                                                 QDate &dateTo,
                                                                 bool filterOn1stAppt,
                                                                 QMap<QString, ReporteBasePtr> &datosReporte,
                                                                 int count)
{
    QString html = "";
    html += "<h1>Resumen de cuestionario entre fechas</h1><br>";
    html += filterOn1stAppt ? "Fecha de primer consulta entre " : "Fecha de primer consulta entre ";
    html += dateFrom.toString() + ", hasta " + dateTo.toString() + "<br>";

    html += "Cantidad de pacientes " + QString::number(count) + "<br>";

    html += "<h2>Detalle</h2><br>";
    foreach (QString key, datosReporte.keys())
    {
        html += key + datosReporte[key]->stats(count);
    }
    return html;
}
