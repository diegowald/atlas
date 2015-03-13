#ifndef DLGLOCALIPS_H
#define DLGLOCALIPS_H

#include <QDialog>

namespace Ui {
class DlgLocalIPs;
}

class DlgLocalIPs : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLocalIPs(QWidget *parent = 0);
    ~DlgLocalIPs();

private:
    Ui::DlgLocalIPs *ui;
};

#endif // DLGLOCALIPS_H
