#ifndef PREGUNTACHECKBOX_H
#define PREGUNTACHECKBOX_H

#include <QObject>
#include "preguntabase.h"
#include "../widgets/wdgtcheckbox.h"


class PreguntaCheckBox : public PreguntaBase
{
public:
    PreguntaCheckBox(const QString &label, const QString &nota, bool showNotes, QObject *parent = 0);
    PreguntaCheckBox(mongo::BSONObj &obj, bool showNotes, QObject *parent = 0);
    ~PreguntaCheckBox();

    virtual PreguntaBasePtr clone();
    virtual QWidget* widget();

    virtual mongo::BSONObj value();

    virtual void applyChanges();
private:
    bool _checked;
    WdgtCheckBox *_widget;
};

#endif // PREGUNTACHECKBOX_H
