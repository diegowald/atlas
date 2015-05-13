#ifndef REPORTS_H
#define REPORTS_H

#include <QObject>
#include <QDialog>
#include "../model/forward.h"

class Reports : public QObject
{
    Q_OBJECT
public:
    explicit Reports(QObject *parent = 0);
    virtual ~Reports();
    QDialog * runContabilizacionPatologiasEntreFechas(QDate &dateFrom, QDate &dateTo, bool filterOn1stAppt, QWidget *parent);
signals:

public slots:

private:
    QString buildReportContabilizacionPatologiasEntreFechas(QDate &dateFrom,
                                                            QDate &dateTo,
                                                            bool filterOn1stAppt,
                                                            QMap<QString, ReporteBasePtr> &datosReporte,
                                                            int count);
};

#endif // REPORTS_H
