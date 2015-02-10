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

    void setData(HistoriaClinicaPtr historia);

private:
    void setAntecedentes(QList<PreguntaBasePtr> &antecedentes);
    void setCuestionario(QList<PreguntaBasePtr> &cuestionario);

private:
    Ui::DialogHistoriaClinica *ui;
};

#endif // DIALOGHISTORIACLINICA_H
