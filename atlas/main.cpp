#include "mainwindow.h"
#include <QApplication>

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

#include <mongo/client/dbclient.h>
#include "dialogs/dialogdbserver.h"
#include "db/dbmanager.h"

int main(int argc, char *argv[])
{

    mongo::client::initialize();
    QApplication a(argc, argv);

    DialogDBServer dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        dbManager::instance()->setDB(dlg.ip());
        MainWindow w;
        w.show();
        return a.exec();
    }
}
