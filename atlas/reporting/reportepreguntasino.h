#ifndef REPORTEPREGUNTASINO_H
#define REPORTEPREGUNTASINO_H

#include <QObject>
#include "reportebase.h"

class ReportePreguntaSiNo : public ReporteBase
{
    Q_OBJECT
public:
    explicit ReportePreguntaSiNo(PreguntaBasePtr pregunta, QObject *parent = 0);
    virtual ~ReportePreguntaSiNo();
    virtual void add(PreguntaBasePtr pregunta);
    virtual QString stats(int total);
signals:

public slots:
private:
    SumarizadorPtr _counterYes;
    SumarizadorPtr _counterNo;
};

#endif // REPORTEPREGUNTASINO_H
