#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model/factory.h"
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void fillView();
    void fillViewAlarmas();
    QString connectionString() const;
    AlarmaPtr getAlarmaPaciente(mongo::OID historiaID);

private slots:
    void on_actionNuevaHistoriaClinica_triggered();

    void on_pushButton_released();

    void on_actionAnalisis_triggered();

    void on_tablePacientes_cellDoubleClicked(int row, int column);

    void on_actionDetectar_mi_IP_triggered();

    void refreshAlarmas();

private:
    Ui::MainWindow *ui;
    Factory* _factory;
    QMap<QString, HistoriaClinicaPtr> _historias;
    QMap<QString, AlarmaPtr> _alarmas;
};

#endif // MAINWINDOW_H
