#ifndef DBSINGLETON_H
#define DBSINGLETON_H

#include <QObject>
#include "idbmanager.h"
#include <QSharedPointer>

class DBSingleton : public IDBManager
{
    Q_OBJECT
public:
    static QSharedPointer<DBSingleton> instance();
    virtual ~DBSingleton();

    // IDBManager interface
public:
    void getAlarmaPaciente(const QString &historiaID);
    void getHistoria(const QString &historiaID);
    void historias(QList<QSharedPointer<queryCondition> > &conditions);

    void alarmas();
    void insertHistoria(HistoriaClinicaPtr historia);
    void updateHistoria(HistoriaClinicaPtr historia);
    void insertAlarma(AlarmaPtr alarma);
    void updateAlarma(AlarmaPtr alarma);
    void existeDNI(const QString &dni, const QString &personaID);

private:
    explicit DBSingleton(QObject *parent = nullptr);

private:
    static QSharedPointer<DBSingleton> _instance;

    QSharedPointer<IDBManager> _dbManager;


};

#endif // DBSINGLETON_H
