#ifndef PREGUNTASINO_H
#define PREGUNTASINO_H

#include <QObject>
#include "preguntabase.h"

class PreguntaSiNo : public PreguntaBase
{
public:
    PreguntaSiNo();
    ~PreguntaSiNo();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
};

#endif // PREGUNTASINO_H
