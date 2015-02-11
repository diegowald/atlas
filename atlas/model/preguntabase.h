#ifndef PREGUNTABASE_H
#define PREGUNTABASE_H

#include <QObject>
#include "forward.h"

class PreguntaBase : public QObject
{
    Q_OBJECT
public:
    explicit PreguntaBase(const QString &label, const QString &nota, QObject *parent = 0);
    ~PreguntaBase();

    virtual void setLabel(const QString &Label);
    virtual void setNota(const QString &Nota);

    virtual QString label() const;
    virtual QString nota() const;

    virtual QWidget *widget(bool includeLabel);
    virtual QWidget *widget() = 0;
    //virtual QString respuesta() = 0;
    virtual PreguntaBasePtr clone() = 0;

private:
    QWidget* widgetWithLabel();

signals:

public slots:
private:
    QString _label;
    QString _nota;
};

#endif // PREGUNTABASE_H
