#ifndef PREGUNTATEXTO_H
#define PREGUNTATEXTO_H

#include <QObject>
#include "preguntabase.h"

class PreguntaTexto : public PreguntaBase
{
public:
    PreguntaTexto();
    ~PreguntaTexto();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

};

#endif // PREGUNTATEXTO_H
