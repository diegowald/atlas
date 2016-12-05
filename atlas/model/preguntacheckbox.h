#ifndef PREGUNTACHECKBOX_H
#define PREGUNTACHECKBOX_H

#include <QObject>
#include "preguntabase.h"
#include "../widgets/wdgtcheckbox.h"


class PreguntaCheckBox : public PreguntaBase
{
public:
    PreguntaCheckBox(const QString &label, const QString &nota, bool showNotes, QObject *parent = 0);
#ifdef USEMONGO
    PreguntaCheckBox(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
#else
    PreguntaCheckBox(QJsonObject &obj, bool showNotes, QObject *parent = 0);
#endif
    ~PreguntaCheckBox();

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

    bool isChecked() const;
private:
    bool _checked;
    WdgtCheckBox *_widget;
};

#endif // PREGUNTACHECKBOX_H
