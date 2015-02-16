#ifndef PREGUNTACOMPUESTA_H
#define PREGUNTACOMPUESTA_H

#include <QObject>
#include "preguntabase.h"
#include "forward.h"

class PreguntaCompuesta : public PreguntaBase
{
public:
    PreguntaCompuesta(const QString &label, const QString &nota, QList<PreguntaBasePtr> &subpreguntas, QObject *parent = 0);
    PreguntaCompuesta(mongo::BSONObj &obj, QObject *parent = 0);
    ~PreguntaCompuesta();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

    virtual mongo::BSONObj value();

    virtual void applyChanges();
private:
    QList<PreguntaBasePtr> _subPreguntas;
};

#endif // PREGUNTACOMPUESTA_H
