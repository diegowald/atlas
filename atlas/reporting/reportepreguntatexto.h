#ifndef REPORTEPREGUNTATEXTO_H
#define REPORTEPREGUNTATEXTO_H

#include <QObject>
#include "reportebase.h"

class ReportePreguntaTexto : public ReporteBase
{
    Q_OBJECT
public:
    explicit ReportePreguntaTexto(PreguntaBasePtr pregunta, QObject *parent = 0);
    virtual ~ReportePreguntaTexto();
    virtual void add(PreguntaBasePtr pregunta);
    virtual QString stats(int total);
signals:

public slots:
private:
    SumarizadorPtr _counterVacios;
    SumarizadorPtr _counterNoVacios;
};

#endif // REPORTEPREGUNTATEXTO_H
