#include "mainwindow.h"
#include <QApplication>

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif
#if USEMONGO
#include <mongo/client/dbclient.h>
#include "db/dbmanager.h"
#else
#include "db/dbrestmanaget.h"
#endif
#include "dialogs/dialogdbserver.h"

#include "db/dbsingleton.h"


int main(int argc, char *argv[])
{
#if USEMONGO
    mongo::client::initialize();
#endif

    QApplication a(argc, argv);

    DialogDBServer dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
#if USEMONGO
        dbManager::instance()->setDB(dlg.ip(), dlg.database(), dlg.username(), dlg.password());
#else
        //DBRestManager::instance()->setDB(dlg.ip(), dlg.database(), dlg.username(), dlg.password());
        DBSingleton::instance()->setParameters(dlg.ip(), dlg.database(), dlg.username(), dlg.password(), dlg.filename());
#endif
        MainWindow w;
        w.show();
        return a.exec();
    }
}
