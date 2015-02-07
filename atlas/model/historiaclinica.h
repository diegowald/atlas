#ifndef HISTORIACLINICA_H
#define HISTORIACLINICA_H

#include <QObject>
#include "forward.h"
#include <QDate>

class HistoriaClinica : public QObject
{
    Q_OBJECT
public:
    explicit HistoriaClinica(PersonaPtr persona, QList<PreguntaBasePtr> &templateAntecedentes,
                             QList<PreguntaBasePtr> &templateCuestionario,
                             QObject *parent = 0);
    ~HistoriaClinica();

signals:

public slots:
private:
    PersonaPtr _persona;
    QDate _fechaPrimerConsulta;
    QDate _fechaSegundaConsulta;
    QList<PreguntaBasePtr> _antecedentes;
    QList<PreguntaBasePtr> _cuestionario;
};

#endif // HISTORIACLINICA_H
