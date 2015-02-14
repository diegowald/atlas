#include "mainwindow.h"
#include <QApplication>
#include <mongo/client/dbclient.h>

int main(int argc, char *argv[])
{

    mongo::client::initialize();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
