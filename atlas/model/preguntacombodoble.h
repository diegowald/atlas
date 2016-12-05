#ifndef PREGUNTACOMBODOBLE_H
#define PREGUNTACOMBODOBLE_H

#include <QObject>
#include <QStringList>
#include "preguntabase.h"
#include "../widgets/wdgtcombodoble.h"

class PreguntaComboDoble : public PreguntaBase
{
public:
    PreguntaComboDoble(const QString &label, const QString &nota, QStringList &lista1, QStringList &lista2, bool showNotes, QObject *parent = 0);

#ifdef USEMONGO
    PreguntaComboDoble(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
#else
    PreguntaComboDoble(QJsonObject &obj, bool showNotes, QObject *parent = 0);
#endif

    ~PreguntaComboDoble();

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

    QStringList opciones1();
    QStringList opciones2();
    QString option1Selected() const;
    QString option2Selected() const;
private:
    QStringList _lista1;
    QStringList _lista2;
    QString _selected1;
    QString _selected2;
    WdgtComboDoble *_widget;
};

#endif // PREGUNTACOMBODOBLE_H
