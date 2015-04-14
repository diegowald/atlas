#ifndef DIALOGDBSERVER_H
#define DIALOGDBSERVER_H

#include <QDialog>

namespace Ui {
class DialogDBServer;
}

class DialogDBServer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDBServer(QWidget *parent = 0);
    ~DialogDBServer();

    QString ip();
    QString database();
    QString username();
    QString password();
private slots:
    void on_radioIPLocal_toggled(bool checked);

    void on_buttonBox_accepted();

private:
    Ui::DialogDBServer *ui;
};

#endif // DIALOGDBSERVER_H
