#ifndef PREGUNTATEXTO_H
#define PREGUNTATEXTO_H

#include <QObject>
#include "preguntabase.h"
#include "../widgets/wdgttexto.h"

class PreguntaTexto : public PreguntaBase
{
public:
    PreguntaTexto(const QString &label, const QString &nota, QObject *parent = 0);
    ~PreguntaTexto();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

    virtual mongo::BSONObj value();
    virtual void applyChanges();
private:
    QString _text;
    WdgtTexto *_widget;
};

#endif // PREGUNTATEXTO_H
