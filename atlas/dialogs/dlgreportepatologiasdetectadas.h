#ifndef DLGREPORTEPATOLOGIASDETECTADAS_H
#define DLGREPORTEPATOLOGIASDETECTADAS_H

#include <QDialog>

namespace Ui {
class DlgReportePatologiasDetectadas;
}

class DlgReportePatologiasDetectadas : public QDialog
{
    Q_OBJECT

public:
    explicit DlgReportePatologiasDetectadas(QWidget *parent = 0);
    ~DlgReportePatologiasDetectadas();

    QDate dateFrom();
    QDate dateTo();
    bool filterOn1stAppt();

private:
    Ui::DlgReportePatologiasDetectadas *ui;
};

#endif // DLGREPORTEPATOLOGIASDETECTADAS_H
