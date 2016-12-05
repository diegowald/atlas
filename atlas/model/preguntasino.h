#ifndef PREGUNTASINO_H
#define PREGUNTASINO_H

#include <QObject>
#include "preguntabase.h"
#include "../widgets/wdgtsino.h"

class PreguntaSiNo : public PreguntaBase
{
public:
    PreguntaSiNo(const QString &label, const QString &nota, bool showNotes, QObject *parent = 0);
#ifdef USEMONGO
    PreguntaSiNo(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
#else
    PreguntaSiNo(QJsonObject &obj, bool showNotes, QObject *parent = 0);
#endif
    ~PreguntaSiNo();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

#if USEMONGO
    virtual mongo::BSONObj value();
#else
    virtual QJsonObject value();
#endif

    virtual void applyChanges();

    virtual QString toHtml();
    virtual QString toHtml(bool incluirNotas);

    bool isYes() const;
private:
    bool _value;
    WdgtSiNo *_widget;
};

#endif // PREGUNTASINO_H
