#ifndef PREGUNTACOMBO_H
#define PREGUNTACOMBO_H

#include <QObject>
#include "preguntabase.h"
#include <QStringList>
#include "../widgets/wdgtcombo.h"

class PreguntaCombo : public PreguntaBase
{
public:
    PreguntaCombo(const QString &label, const QString &nota, QStringList &listaValores, bool showNotes, QObject *parent = 0);
    PreguntaCombo(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
    ~PreguntaCombo();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
    virtual void applyChanges();

    virtual mongo::BSONObj value();
private:
    QStringList _listaValores;
    QString _selectedValue;
    WdgtCombo *_widget;
};

#endif // PREGUNTACOMBO_H
