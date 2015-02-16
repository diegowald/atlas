#ifndef PREGUNTABASE_H
#define PREGUNTABASE_H

#include <QObject>
#include "forward.h"
#include "../db/serializable.h"

class PreguntaBase : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit PreguntaBase(const QString &label, const QString &nota, const QString &type, QObject *parent = 0);
    PreguntaBase(mongo::BSONObj &obj, QObject *parent = 0);
    ~PreguntaBase();

    virtual void setLabel(const QString &Label);
    virtual void setNota(const QString &Nota);

    virtual QString label() const;
    virtual QString nota() const;

    virtual QWidget *widget(bool includeLabel);
    virtual QWidget *widget() = 0;
    //virtual QString respuesta() = 0;
    virtual PreguntaBasePtr clone() = 0;

    virtual void applyChanges() = 0;

    virtual mongo::BSONObj toBson();
    virtual mongo::BSONObj value() = 0;

private:
    QWidget* widgetWithLabel();

signals:

public slots:
private:
    QString _label;
    QString _nota;
    QString _type;
};

#endif // PREGUNTABASE_H
