#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model/factory.h"

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

private slots:
    void on_actionNuevaHistoriaClinica_triggered();

    void on_pushButton_released();

    void on_actionAnalisis_triggered();

private:
    Ui::MainWindow *ui;
    Factory* _factory;
    QList<HistoriaClinicaPtr> _historias;
};

#endif // MAINWINDOW_H
