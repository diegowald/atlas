#ifndef BLOCKINGHTTP_H
#define BLOCKINGHTTP_H

#include <QObject>
#include "httprequestworker.h"

class BlockingHttp : public QObject
{
    Q_OBJECT
public:
    explicit BlockingHttp(const QString &url, const QString &callType, QObject *parent = 0);

    QString execute();
signals:

private slots:
    void on_execution_finished(HttpRequestWorker *worker);

private:
    QString _result;
    bool _finished;
    bool _isError;
    QString _url;
    QString _callType;
    HttpRequestWorker *_worker;
    HttpRequestInput *_req;
};

#endif // BLOCKINGHTTP_H
