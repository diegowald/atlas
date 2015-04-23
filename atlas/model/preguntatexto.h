#ifndef PREGUNTATEXTO_H
#define PREGUNTATEXTO_H

#include <QObject>
#include "preguntabase.h"
#include "../widgets/wdgttexto.h"

class PreguntaTexto : public PreguntaBase
{
public:
    PreguntaTexto(const QString &label, const QString &nota, bool showNotes, QObject *parent = 0);
    PreguntaTexto(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
    ~PreguntaTexto();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

    virtual mongo::BSONObj value();
    virtual void applyChanges();

    virtual QString toHtml();
    virtual QString toHtml(bool incluirNotas);
private:
    QString _text;
    WdgtTexto *_widget;
};

#endif // PREGUNTATEXTO_H
