#ifndef DBRESTMANAGET_H
#define DBRESTMANAGET_H

#include <QObject>
#include "model/factory.h"
#include "httprequestworker.h"

class DBRestManager : public QObject
{
    Q_OBJECT
public:
    virtual ~DBRestManager();

    static DBRestManager* instance();

    //void setDB(const QString &server, const QString &databaseName, const QString &user, const QString &password);

    void getAlarmaPaciente(const QString &historiaID);
    void getHistoria(const QString &historiaID);
    void historias(const QString query);

    void alarmas();


    void insertHistoria(HistoriaClinicaPtr historia);
    void updateHistoria(HistoriaClinicaPtr historia);

    void insertAlarma(AlarmaPtr alarma);
    void updateAlarma(AlarmaPtr alarma);

    void existeDNI(const QString &dni, const QString &personaID);

protected:
    QString connectionString() const;
    //void connectToDatabase(mongo::DBClientConnection &conn);

private:
    explicit DBRestManager(QObject *parent = 0);

    void error(const QString &operacion, const QString &mensaje);

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

private slots:
    void on_getAlarmaPaciente_finished(HttpRequestWorker *worker);
    void on_getHistoria_finished(HttpRequestWorker *worker);
    void on_historias_finished(HttpRequestWorker *worker);

    void on_alarmas_finished(HttpRequestWorker *worker);


    void on_insertHistoria_finished(HttpRequestWorker *worker);
    void on_updateHistoria_finished(HttpRequestWorker *worker);

    void on_insertAlarma_finished(HttpRequestWorker *worker);
    void on_updateAlarma_finished(HttpRequestWorker *worker);

    void on_existeDNI_finished(HttpRequestWorker *worker);

public slots:



private:
    static DBRestManager *_instance;

    Factory *_factory;

    QString _connection;
    QString _server;

    QString _databaseName;
    QString _user;
    QString _password;

    QString _apiKey;
    QString _baseURL;
};

#endif // DBRESTMANAGET_H
