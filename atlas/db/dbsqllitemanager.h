#ifndef DBSQLLITEMANAGER_H
#define DBSQLLITEMANAGER_H

#include <QObject>
#include "model/factory.h"
#include <QtSql/QSqlDatabase>
#include <QMap>
#include <QSharedPointer>
#include "idbmanager.h"

class DBSqlLiteManager : public IDBManager
{
    Q_OBJECT
public:
    explicit DBSqlLiteManager(QObject *parent = nullptr);
    virtual ~DBSqlLiteManager();

    void getAlarmaPaciente(const QString &historiaID);
    void getHistoria(const QString &historiaID);
    void historias(const QString query);
    virtual void historias(QList<QSharedPointer<queryCondition> > &conditions);

    void alarmas();


    void insertHistoria(HistoriaClinicaPtr historia);
    void updateHistoria(HistoriaClinicaPtr historia);

    void insertAlarma(AlarmaPtr alarma);
    void updateAlarma(AlarmaPtr alarma);

    void existeDNI(const QString &dni, const QString &personaID);

protected:
    QString connectionString() const;
    
private:
    void error(const QString &operacion, const QString &mensaje);

    QSqlDatabase getDB();
    
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

private:
    Factory *_factory;

    QString _connection;
    QString _server;

    QString _databaseName;
    QString _user;
    QString _password;

    QString _apiKey;
    QString _baseURL;
};

#endif // DBSQLLITEMANAGER_H
