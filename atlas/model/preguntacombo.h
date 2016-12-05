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
#ifdef USEMONGO
    PreguntaCombo(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
#else
    PreguntaCombo(QJsonObject &obj, bool showNotes, QObject *parent = 0);
#endif

    ~PreguntaCombo();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();
    virtual void applyChanges();

#ifdef USEMONGO
    virtual mongo::BSONObj value();
#else
    virtual QJsonObject value();
#endif
    virtual QString toHtml();
    virtual QString toHtml(bool incluirNotas);

    QString optionSelected() const;
    QStringList  opciones();
private:
    QStringList _listaValores;
    QString _selectedValue;
    WdgtCombo *_widget;
};

#endif // PREGUNTACOMBO_H
