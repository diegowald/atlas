#ifndef DIALOGHISTORIACLINICA_H
#define DIALOGHISTORIACLINICA_H

#include <QDialog>

namespace Ui {
class DialogHistoriaClinica;
}

class DialogHistoriaClinica : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHistoriaClinica(QWidget *parent = 0);
    ~DialogHistoriaClinica();

private:
    Ui::DialogHistoriaClinica *ui;
};

#endif // DIALOGHISTORIACLINICA_H
