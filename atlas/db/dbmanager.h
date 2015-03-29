#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include "model/forward.h"
#include <mongo/client/dbclient.h>
#include "model/factory.h"

class dbManager : public QObject
{
    Q_OBJECT
public:
    virtual ~dbManager();

    static dbManager* instance();

    AlarmaPtr getAlarmaPaciente(mongo::OID historiaID);
    HistoriaClinicaPtr getHistoria(mongo::OID historiaID);
    QMap<QString, HistoriaClinicaPtr> historias(const QString query);

    QMap<QString, AlarmaPtr> alarmas();
    QString connectionString() const;

    void insertHistoria(HistoriaClinicaPtr historia);
    void updateHistoria(HistoriaClinicaPtr historia);

    void insertAlarma(AlarmaPtr alarma);
    void updateAlarma(AlarmaPtr alarma);

private:
    explicit dbManager(QObject *parent = 0);

    void error(const QString &operacion, const QString &mensaje);

signals:

public slots:


private:
    static dbManager *_instance;

    Factory *_factory;
};

#endif // DBMANAGER_H
