#ifndef PREGUNTACOMBODOBLE_H
#define PREGUNTACOMBODOBLE_H

#include <QObject>
#include "preguntabase.h"

class PreguntaComboDoble : public PreguntaBase
{
public:
    PreguntaComboDoble();
    ~PreguntaComboDoble();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

};

#endif // PREGUNTACOMBODOBLE_H
