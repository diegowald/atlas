#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model/factory.h"
#include <QMap>
#include <QTableWidgetItem>
#include <QtPrintSupport/QPrinter>

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
#if USEMONGO
    AlarmaPtr getAlarmaPaciente(mongo::OID historiaID);
#else
    AlarmaPtr getAlarmaPaciente(const QString &historiaID);
#endif
private slots:
    void on_actionNuevaHistoriaClinica_triggered();

    void on_pushButton_released();

    void on_actionAnalisis_triggered();

    void on_tablePacientes_cellDoubleClicked(int row, int column);

    void on_actionDetectar_mi_IP_triggered();

    void refreshAlarmas();

    void on_tableAlarmas_cellDoubleClicked(int row, int column);

    void on_actionImprimir_Historia_Clinica_triggered();

    void print(QPrinter *printer);
    void on_actionVista_PreviaHistoriaClinica_triggered();

    void on_tablePacientes_itemSelectionChanged();

    void on_actionContabilizacion_Patologias_entre_Fechas_triggered();

    void on_alarmaReturned(AlarmaPtr alarma, bool error);
    void on_historiasReturned(QMap<QString, HistoriaClinicaPtr> historias, bool error);
    void on_alarmasReturned(QMap<QString, AlarmaPtr> alarmas, bool error);

    void on_historiaInserted(HistoriaClinicaPtr historia, bool error);
    void on_historiaUpdated(HistoriaClinicaPtr historia, bool error);

    void on_alarmaInserted(AlarmaPtr alarma, bool error);
    void on_alarmaUpdated(AlarmaPtr alarma, bool error);

    void on_existeDNIReturned(const QString &dni, const QString &personaID, bool exists);

private:
    Ui::MainWindow *ui;
    Factory* _factory;
    QMap<QString, HistoriaClinicaPtr> _historias;
    QMap<QString, AlarmaPtr> _alarmas;

    QString _idHistoria;
    QString _html;
};

#endif // MAINWINDOW_H
