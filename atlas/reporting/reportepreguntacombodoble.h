#ifndef REPORTEPREGUNTACOMBODOBLE_H
#define REPORTEPREGUNTACOMBODOBLE_H

#include <QObject>
#include "reportebase.h"
#include <QMap>

class ReportePreguntaComboDoble : public ReporteBase
{
    Q_OBJECT
public:
    explicit ReportePreguntaComboDoble(PreguntaBasePtr pregunta, QObject *parent = 0);
    virtual ~ReportePreguntaComboDoble();
    virtual void add(PreguntaBasePtr pregunta);
    virtual QString stats(int total);
signals:

public slots:
private:
    QMap<QString, QMap<QString, SumarizadorPtr>> _counterOpciones;
};

#endif // REPORTEPREGUNTACOMBODOBLE_H
