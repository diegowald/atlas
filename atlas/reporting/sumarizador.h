#ifndef SUMARIZADOR_H
#define SUMARIZADOR_H

#include <QObject>

class Sumarizador : public QObject
{
    Q_OBJECT
public:
    explicit Sumarizador(const QString &label, QObject *parent = 0);
    void increment();
    int count();

signals:

public slots:

private:
    QString _label;
    int _count;
};

#endif // SUMARIZADOR_H
