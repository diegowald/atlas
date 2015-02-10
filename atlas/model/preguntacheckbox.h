#ifndef PREGUNTACHECKBOX_H
#define PREGUNTACHECKBOX_H

#include <QObject>
#include "preguntabase.h"

class PreguntaCheckBox : public PreguntaBase
{
public:
    PreguntaCheckBox();
    ~PreguntaCheckBox();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
};

#endif // PREGUNTACHECKBOX_H
