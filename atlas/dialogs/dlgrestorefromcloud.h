#ifndef DLGRESTOREFROMCLOUD_H
#define DLGRESTOREFROMCLOUD_H

#include <QDialog>
#include "db/dbrestmanaget.h"


namespace Ui {
class DlgRestoreFromCloud;
}

class DlgRestoreFromCloud : public QDialog
{
    Q_OBJECT

public:
    explicit DlgRestoreFromCloud(QWidget *parent = 0);
    ~DlgRestoreFromCloud();

private:
    Ui::DlgRestoreFromCloud *ui;

};

#endif // DLGRESTOREFROMCLOUD_H
