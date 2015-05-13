#ifndef REPORTEBASE_H
#define REPORTEBASE_H

#include <QObject>
#include "../model/forward.h"
#include "sumarizador.h"
class ReporteBase : public QObject
{
    Q_OBJECT
public:
    explicit ReporteBase(PreguntaBasePtr pregunta, QObject *parent = 0);
    virtual ~ReporteBase();

    virtual void add(PreguntaBasePtr pregunta) = 0;
    virtual QString stats(int total) = 0;
signals:

public slots:

protected:
    QList<PreguntaBasePtr> _preguntas;
    SumarizadorPtr _counter;
};

#endif // REPORTEBASE_H
