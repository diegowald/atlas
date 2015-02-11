#ifndef PREGUNTACOMBO_H
#define PREGUNTACOMBO_H

#include <QObject>
#include "preguntabase.h"
#include <QStringList>

class PreguntaCombo : public PreguntaBase
{
public:
    PreguntaCombo(const QString &label, const QString &nota, QStringList &listaValores, QObject *parent = 0);
    ~PreguntaCombo();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
private:
    QStringList _listaValores;
};

#endif // PREGUNTACOMBO_H
