#ifndef PREGUNTACHECKBOX_H
#define PREGUNTACHECKBOX_H

#include <QObject>
#include "preguntabase.h"

class PreguntaCheckBox : public PreguntaBase
{
public:
    PreguntaCheckBox(const QString &label, const QString &nota, QObject *parent = 0);
    ~PreguntaCheckBox();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
};

#endif // PREGUNTACHECKBOX_H
