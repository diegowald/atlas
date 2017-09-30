#ifndef IDBMANAGER_H
#define IDBMANAGER_H


#include <QObject>
#include "model/factory.h"
#include <QMap>
#include <QSharedPointer>
#include <QList>
#include <db/querycondition.h>

class IDBManager : public QObject
{
    Q_OBJECT
public:
    IDBManager(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IDBManager() {}

    virtual void setParameters(const QString &ip, const QString &database, const QString & username, const QString &password, const QString &filename) = 0;

    virtual void getAlarmaPaciente(const QString &historiaID) = 0;
    virtual void getHistoria(const QString &historiaID) = 0;
    //virtual void historias(const QString query) = 0;
    virtual void historias(QList<QSharedPointer<queryCondition> > &conditions) = 0;

    virtual void alarmas() = 0;


    virtual void insertHistoria(HistoriaClinicaPtr historia) = 0;
    virtual void updateHistoria(HistoriaClinicaPtr historia) = 0;

    virtual void insertAlarma(AlarmaPtr alarma) = 0;
    virtual void updateAlarma(AlarmaPtr alarma) = 0;

    virtual void existeDNI(const QString &dni, const QString &personaID) = 0;



signals:
    void alarmaReturned(AlarmaPtr alarma, bool error);
    void historiaReturned(HistoriaClinicaPtr historia, bool error);
    void historiasReturned(QMap<QString, HistoriaClinicaPtr> historias, bool error);
    void alarmasReturned(QMap<QString, AlarmaPtr> alarmas, bool error);

    void historiaInserted(HistoriaClinicaPtr historia, bool error);
    void historiaUpdated(HistoriaClinicaPtr historia, bool error);

    void alarmaInserted(AlarmaPtr alarma, bool error);
    void alarmaUpdated(AlarmaPtr alarma, bool error);

    void existeDNIReturned(const QString &dni, const QString &personaID, bool exists, bool error);
};



#endif // IDBMANAGER_H
