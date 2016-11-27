#include "blockinghttp.h"
#include <QThread>
#include <QApplication>

BlockingHttp::BlockingHttp(const QString &url, const QString &callType, QObject *parent) : QObject(parent)
{
    _result = "";
    _finished = false;
    _isError = false;
    _url = url;
    _callType = callType;

}

QString BlockingHttp::execute()
{
    _req = new HttpRequestInput(_url, _callType);
    _worker = new HttpRequestWorker(this);
    connect(_worker, &HttpRequestWorker::on_execution_finished, this, &BlockingHttp::on_execution_finished);

    _worker->execute(_req);

    while (!_finished)
    {
        QThread::msleep(500);
        QApplication::processEvents();
    }
    return _result;
}


void BlockingHttp::on_execution_finished(HttpRequestWorker *worker)
{

    QString msg;

     if (worker->error_type == QNetworkReply::NoError)
     {
         // communication was successful
         msg = worker->response;
         _isError = false;
     }
     else
     {
         // an error occurred
         msg = worker->error_str;
         _isError = true;
     }
     _finished = true;
}
