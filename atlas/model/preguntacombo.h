#ifndef PREGUNTACOMBO_H
#define PREGUNTACOMBO_H

#include <QObject>
#include "preguntabase.h"

class PreguntaCombo : public PreguntaBase
{
public:
    PreguntaCombo();
    ~PreguntaCombo();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

};

#endif // PREGUNTACOMBO_H
