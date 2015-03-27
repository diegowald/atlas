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

private slots:
    void on_btnRealizado_released();

private:
    Ui::DlgSetAlarma *ui;
    bool _realizado;
};

#endif // DLGSETALARMA_H
