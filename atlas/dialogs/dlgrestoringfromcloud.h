#ifndef DLGRESTORINGFROMCLOUD_H
#define DLGRESTORINGFROMCLOUD_H

#include <QDialog>
#include "db/dbrestmanaget.h"


namespace Ui {
class DlgRestoringFromCloud;
}

class DlgRestoringFromCloud : public QDialog
{
    Q_OBJECT

public:
    explicit DlgRestoringFromCloud(QWidget *parent = 0);
    ~DlgRestoringFromCloud();
private:
    void startProcess();

private slots:
    void on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias, bool error);
    void on_alarmasReturned(QMap<QString, AlarmaPtr> alarmas, bool error);

private:
    Ui::DlgRestoringFromCloud *ui;
    DBRestManager _cloud;
};

#endif // DLGRESTORINGFROMCLOUD_H
