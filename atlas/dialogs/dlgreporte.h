#ifndef DLGREPORTE_H
#define DLGREPORTE_H

#include <QDialog>

namespace Ui {
class DlgReporte;
}

class DlgReporte : public QDialog
{
    Q_OBJECT

public:
    explicit DlgReporte(QWidget *parent = 0);
    ~DlgReporte();

    void setReportData(const QString &html);

private:
    Ui::DlgReporte *ui;
};

#endif // DLGREPORTE_H
