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

private slots:
    void on_actionNuevaHistoriaClinica_triggered();

private:
    Ui::MainWindow *ui;
    Factory* _factory;
};

#endif // MAINWINDOW_H
