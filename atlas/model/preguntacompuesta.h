#ifndef PREGUNTACOMPUESTA_H
#define PREGUNTACOMPUESTA_H

#include <QObject>
#include "preguntabase.h"
#include "forward.h"
#include "../widgets/wdgtcompuesto.h"

class PreguntaCompuesta : public PreguntaBase
{
public:
    PreguntaCompuesta(const QString &label, const QString &nota, QList<PreguntaBasePtr> &subpreguntas, bool showNotes, QObject *parent = 0);
    PreguntaCompuesta(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
    ~PreguntaCompuesta();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

    virtual mongo::BSONObj value();

    virtual void applyChanges();

    virtual QString toHtml();
    virtual QString toHtml(bool incluirNotas);

    QList<PreguntaBasePtr> subPreguntas();
    bool isChecked() const;

private:
    QList<PreguntaBasePtr> _subPreguntas;
    bool _checked;
    WdgtCompuesto *_widget;
};

#endif // PREGUNTACOMPUESTA_H
