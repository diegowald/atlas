#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include "model/forward.h"

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

#include <mongo/client/dbclient.h>
#include "model/factory.h"

class dbManager : public QObject
{
    Q_OBJECT
public:
    virtual ~dbManager();

    static dbManager* instance();

    void setDB(const QString &server, const QString &databaseName, const QString &user, const QString &password);

    AlarmaPtr getAlarmaPaciente(mongo::OID historiaID);
    HistoriaClinicaPtr getHistoria(mongo::OID historiaID);
    QMap<QString, HistoriaClinicaPtr> historias(const QString query);

    QMap<QString, AlarmaPtr> alarmas();


    void insertHistoria(HistoriaClinicaPtr historia);
    void updateHistoria(HistoriaClinicaPtr historia);

    void insertAlarma(AlarmaPtr alarma);
    void updateAlarma(AlarmaPtr alarma);

    bool existeDNI(const QString &dni, mongo::OID personaID);

protected:
    QString connectionString() const;
    void connectToDatabase(mongo::DBClientConnection &conn);

private:
    explicit dbManager(QObject *parent = 0);

    void error(const QString &operacion, const QString &mensaje);

signals:

public slots:


private:
    static dbManager *_instance;

    Factory *_factory;

    QString _connection;
    QString _server;

    QString _databaseName;
    QString _user;
    QString _password;
};

#endif // DBMANAGER_H
