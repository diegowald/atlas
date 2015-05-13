#ifndef REPORTEPREGUNTACOMBO_H
#define REPORTEPREGUNTACOMBO_H

#include <QObject>
#include "reportebase.h"
#include <QMap>


class ReportePreguntaCombo : public ReporteBase
{
    Q_OBJECT
public:
    explicit ReportePreguntaCombo(PreguntaBasePtr pregunta, QObject *parent = 0);
    virtual ~ReportePreguntaCombo();
    virtual void add(PreguntaBasePtr pregunta);
    virtual QString stats(int total);
signals:

public slots:
private:
    QMap<QString, SumarizadorPtr> _opciones;
};

#endif // REPORTEPREGUNTACOMBO_H
