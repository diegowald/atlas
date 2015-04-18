#ifndef DIALOGHISTORIACLINICA_H
#define DIALOGHISTORIACLINICA_H

#include <QDialog>
#include "model/forward.h"
#include <QGridLayout>

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
    bool alarmaNueva() const;

private slots:
    void on_btnAlarma_released();

private:
    void setAntecedentes(QList<PreguntaBasePtr> &antecedentes);
    void setTestKinesiologico(QList<PreguntaBasePtr> &testKinesiologico);
    void setCuestionario(QList<PreguntaBasePtr> &cuestionario, QGridLayout *grid);

    void applyAntecedentes();
    void applyTestKinesiologico();
    void applyCuestionario();

private:
    Ui::DialogHistoriaClinica *ui;
    HistoriaClinicaPtr _historia;
    AlarmaPtr _alarma;
    bool _alarmaNueva;
    bool _esPrimerConsulta;
};

#endif // DIALOGHISTORIACLINICA_H
