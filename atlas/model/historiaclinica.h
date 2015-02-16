#ifndef HISTORIACLINICA_H
#define HISTORIACLINICA_H

#include <QObject>
#include "forward.h"
#include <QDate>
#include "../db/serializable.h"

class HistoriaClinica : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit HistoriaClinica(PersonaPtr persona, QList<PreguntaBasePtr> &templateAntecedentes,
                             QList<PreguntaBasePtr> &templateCuestionario,
                             QObject *parent = 0);

    HistoriaClinica(mongo::BSONObj &obj, QObject *parent = 0);

    ~HistoriaClinica();

    PersonaPtr persona();
    QDate fechaPrimerConsulta();
    QDate fechaSegundaConsulta();
    QString numeroPaciente();
    QList<PreguntaBasePtr> &antecedentes();
    QList<PreguntaBasePtr> &cuestionario();

    void setFechaPrimerConsulta(QDate &date);
    void setFechaSegundaConsulta(QDate &date);
    void setNumeroPaciente(const QString &nro);

    virtual mongo::BSONObj toBson();

private:
    mongo::BSONObj arrayBson(QList<PreguntaBasePtr> list);
    void fromArrayBson(std::vector<mongo::BSONElement> &arr, QList<PreguntaBasePtr> &list);

signals:

public slots:
private:
    PersonaPtr _persona;
    QDate _fechaPrimerConsulta;
    QDate _fechaSegundaConsulta;
    QList<PreguntaBasePtr> _antecedentes;
    QList<PreguntaBasePtr> _cuestionario;
    QString _numeroPaciente;
};

#endif // HISTORIACLINICA_H
