#ifndef PREGUNTASINO_H
#define PREGUNTASINO_H

#include <QObject>
#include "preguntabase.h"

class PreguntaSiNo : public PreguntaBase
{
public:
    PreguntaSiNo(const QString &label, const QString &nota, QObject *parent = 0);
    ~PreguntaSiNo();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
};

#endif // PREGUNTASINO_H
