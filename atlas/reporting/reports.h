#ifndef REPORTS_H
#define REPORTS_H

#include <QObject>
#include <QDialog>
#include "../model/forward.h"
#include "../dialogs/dlgreporte.h"
#include <QDate>
#include <QSharedPointer>
#include <QMap>

class Reports : public QObject
{
    Q_OBJECT
public:
    explicit Reports(QObject *parent = 0);
    virtual ~Reports();
    QDialog * runContabilizacionPatologiasEntreFechas(QDate &dateFrom, QDate &dateTo, bool filterOn1stAppt, QWidget *parent);
signals:

public slots:

#ifndef USEMONGO
private slots:
    void on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias);
#endif

private:
    QString buildReportContabilizacionPatologiasEntreFechas(QDate &dateFrom,
                                                            QDate &dateTo,
                                                            bool filterOn1stAppt,
                                                            QMap<QString, ReporteBasePtr> &datosReporte,
                                                            int count);

    DlgReporte* _dlg;
    QDate _dateFrom;
    QDate _dateTo;
    bool _filterOn1stAppt;
};

#endif // REPORTS_H
