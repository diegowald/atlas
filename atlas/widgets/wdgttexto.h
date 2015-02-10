#ifndef WDGTTEXTO_H
#define WDGTTEXTO_H

#include <QWidget>

namespace Ui {
class WdgtTexto;
}

class WdgtTexto : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtTexto(QWidget *parent = 0);
    ~WdgtTexto();

private:
    Ui::WdgtTexto *ui;
};

#endif // WDGTTEXTO_H
