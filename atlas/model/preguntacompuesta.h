#ifndef PREGUNTACOMPUESTA_H
#define PREGUNTACOMPUESTA_H

#include <QObject>
#include "preguntabase.h"
#include "forward.h"

class PreguntaCompuesta : public PreguntaBase
{
public:
    PreguntaCompuesta();
    ~PreguntaCompuesta();

private:
    QList<PreguntaBasePtr> _subPreguntas;
};

#endif // PREGUNTACOMPUESTA_H
