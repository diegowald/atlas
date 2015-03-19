#ifndef DLGSETALARMA_H
#define DLGSETALARMA_H

#include <QDialog>
#include "model/forward.h"


namespace Ui {
class DlgSetAlarma;
}

class DlgSetAlarma : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSetAlarma(QWidget *parent = 0);
    ~DlgSetAlarma();
    void setData(AlarmaPtr value);
    void updateData(AlarmaPtr alarma);

private:
    Ui::DlgSetAlarma *ui;
};

#endif // DLGSETALARMA_H
