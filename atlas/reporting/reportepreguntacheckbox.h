#ifndef REPORTEPREGUNTACHECKBOX_H
#define REPORTEPREGUNTACHECKBOX_H

#include <QObject>
#include "reportebase.h"

class ReportePreguntaCheckBox : public ReporteBase
{
    Q_OBJECT
public:
    explicit ReportePreguntaCheckBox(PreguntaBasePtr pregunta, QObject *parent = 0);
    virtual ~ReportePreguntaCheckBox();
    virtual void add(PreguntaBasePtr pregunta);
    virtual QString stats(int total);
signals:
public slots:
private:
    SumarizadorPtr _checked;
    SumarizadorPtr _unchecked;
};

#endif // REPORTEPREGUNTACHECKBOX_H
