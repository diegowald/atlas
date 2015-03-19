#ifndef DIALOGHISTORIACLINICA_H
#define DIALOGHISTORIACLINICA_H

#include <QDialog>
#include "model/forward.h"

namespace Ui {
class DialogHistoriaClinica;
}

class DialogHistoriaClinica : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHistoriaClinica(QWidget *parent = 0);
    ~DialogHistoriaClinica();

    void setData(HistoriaClinicaPtr historia, AlarmaPtr alarma);
    void applyData();

    AlarmaPtr alarma();


private slots:
    void on_btnAlarma_released();

private:
    void setAntecedentes(QList<PreguntaBasePtr> &antecedentes);
    void setCuestionario(QList<PreguntaBasePtr> &cuestionario);

    void applyAntecedentes();
    void applyCuestionario();

private:
    Ui::DialogHistoriaClinica *ui;
    HistoriaClinicaPtr _historia;
    AlarmaPtr _alarma;
};

#endif // DIALOGHISTORIACLINICA_H
