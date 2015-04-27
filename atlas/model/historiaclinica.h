#ifndef HISTORIACLINICA_H
#define HISTORIACLINICA_H

#include <QObject>
#include "forward.h"
#include <QDate>
#include "../db/serializable.h"
#include "htmlable.h"

class HistoriaClinica : public QObject, public Serializable, public htmlAble
{
    Q_OBJECT
public:
    explicit HistoriaClinica(PersonaPtr persona, QList<PreguntaBasePtr> &templateAntecedentes, QList<PreguntaBasePtr> &templateTestKinesiologico1erConsulta, QList<PreguntaBasePtr> &templateTestKinesiologico2daConsulta,
                             QList<PreguntaBasePtr> &templateCuestionario1erConsulta, QList<PreguntaBasePtr> &templateCuestionario2daConsulta,
                             QObject *parent = 0);

    HistoriaClinica(mongo::BSONObj &obj, QObject *parent = 0);

    ~HistoriaClinica();

    PersonaPtr persona();
    QDate fechaPrimerConsulta();
    QDate fechaSegundaConsulta();
    QString numeroPaciente();
    QList<PreguntaBasePtr> &antecedentes();
    QList<PreguntaBasePtr> &testKinesiologico1erConsulta();
    QList<PreguntaBasePtr> &testKinesiologico2darConsulta();
    QList<PreguntaBasePtr> &cuestionario1erConsulta();
    QList<PreguntaBasePtr> &cuestionario2daConsulta();
    QString idString();
    mongo::OID id();

    void setFechaPrimerConsulta(QDate &date);
    void setFechaSegundaConsulta(QDate &date);
    void setNumeroPaciente(const QString &nro);

    virtual mongo::BSONObj toBson();

    virtual QString toHtml();

private:
    mongo::BSONObj arrayBson(QList<PreguntaBasePtr> list);
    void fromArrayBson(std::vector<mongo::BSONElement> &arr, QList<PreguntaBasePtr> &list);
    QString html(QList<PreguntaBasePtr> &lista, int cantColumnas);
signals:

public slots:
private:
    PersonaPtr _persona;
    QDate _fechaPrimerConsulta;
    QDate _fechaSegundaConsulta;
    QList<PreguntaBasePtr> _antecedentes;
    QList<PreguntaBasePtr> _testKinesiologico1erConsulta;
    QList<PreguntaBasePtr> _testKinesiologico2daConsulta;
    QList<PreguntaBasePtr> _cuestionario1erConsulta;
    QList<PreguntaBasePtr> _cuestionario2daConsulta;
    QString _numeroPaciente;
    mongo::OID _id;
};

#endif // HISTORIACLINICA_H
