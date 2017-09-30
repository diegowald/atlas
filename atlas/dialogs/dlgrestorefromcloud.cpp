#include "dlgrestorefromcloud.h"
#include "ui_dlgrestorefromcloud.h"


DlgRestoreFromCloud::DlgRestoreFromCloud(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgRestoreFromCloud)
{
    ui->setupUi(this);

}

DlgRestoreFromCloud::~DlgRestoreFromCloud()
{
    delete ui;
}

