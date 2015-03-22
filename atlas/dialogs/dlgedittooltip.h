#ifndef DLGEDITTOOLTIP_H
#define DLGEDITTOOLTIP_H

#include <QDialog>

namespace Ui {
class DlgEditTooltip;
}

class DlgEditTooltip : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditTooltip(QWidget *parent = 0);
    ~DlgEditTooltip();

    void setData(const QString &value);
    QString data();

private:
    Ui::DlgEditTooltip *ui;
};

#endif // DLGEDITTOOLTIP_H
