#ifndef DBSINGLETON_H
#define DBSINGLETON_H

#include <QObject>
#include "idbmanager.h"
#include <QSharedPointer>

class DBSingleton : public IDBManager
{
    Q_OBJECT
public:
    static DBSingleton* instance();
    virtual ~DBSingleton();

    void setParameters(const QString &ip, const QString &database, const QString & username, const QString &password, const QString &filename);

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

private slots:
    void on_alarmaReturned(AlarmaPtr alarma, bool error);
    void on_historiaReturned(HistoriaClinicaPtr historia, bool error);
    void on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias, bool error);
    void on_alarmasReturned(QMap<QString, AlarmaPtr> alarmas, bool error);

    void on_historiaInserted(HistoriaClinicaPtr historia, bool error);
    void on_historiaUpdated(HistoriaClinicaPtr historia, bool error);

    void on_alarmaInserted(AlarmaPtr alarma, bool error);
    void on_alarmaUpdated(AlarmaPtr alarma, bool error);

    void on_existeDNIReturned(const QString &dni, const QString &personaID, bool exists, bool error);

private:
    static DBSingleton* _instance;

    IDBManager* _dbManager;


};

#endif // DBSINGLETON_H
