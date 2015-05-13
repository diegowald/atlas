#ifndef REPORTEPREGUNTACOMPUESTA_H
#define REPORTEPREGUNTACOMPUESTA_H

#include <QObject>
#include "reportebase.h"
#include <QMap>

class ReportePreguntaCompuesta : public ReporteBase
{
    Q_OBJECT
public:
    explicit ReportePreguntaCompuesta(PreguntaBasePtr pregunta, QObject *parent = 0);
    virtual ~ReportePreguntaCompuesta();
    virtual void add(PreguntaBasePtr pregunta);
    virtual QString stats(int total);
signals:

public slots:
private:
    QMap<QString, ReporteBasePtr> _subReportes;
};

#endif // REPORTEPREGUNTACOMPUESTA_H
