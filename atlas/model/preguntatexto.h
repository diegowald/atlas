#ifndef PREGUNTATEXTO_H
#define PREGUNTATEXTO_H

#include <QObject>
#include "preguntabase.h"
#include "../widgets/wdgttexto.h"

class PreguntaTexto : public PreguntaBase
{
public:
    PreguntaTexto(const QString &label, const QString &nota, bool showNotes, QObject *parent = 0);
#ifdef USEMONGO
    PreguntaTexto(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
#else
    PreguntaTexto(QJsonObject &obj, bool showNotes, QObject *parent = 0);
#endif
    ~PreguntaTexto();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

#ifdef USEMONGO
    virtual mongo::BSONObj value();
#else
    virtual QJsonObject value();
#endif

    virtual void applyChanges();

    virtual QString toHtml();
    virtual QString toHtml(bool incluirNotas);

    QString text() const;
private:
    QString _text;
    WdgtTexto *_widget;
};

#endif // PREGUNTATEXTO_H
