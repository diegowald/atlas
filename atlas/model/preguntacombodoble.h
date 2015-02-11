#ifndef PREGUNTACOMBODOBLE_H
#define PREGUNTACOMBODOBLE_H

#include <QObject>
#include <QStringList>
#include "preguntabase.h"

class PreguntaComboDoble : public PreguntaBase
{
public:
    PreguntaComboDoble(const QString &label, const QString &nota, QStringList &lista1, QStringList &lista2, QObject *parent = 0);
    ~PreguntaComboDoble();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
private:
    QStringList _lista1;
    QStringList _lista2;
};

#endif // PREGUNTACOMBODOBLE_H
