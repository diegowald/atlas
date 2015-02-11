#ifndef WDGTCOMBO_H
#define WDGTCOMBO_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class WdgtCombo;
}

class WdgtCombo : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtCombo(QWidget *parent = 0);
    ~WdgtCombo();

    void setLista(QStringList &lista);

private:
    Ui::WdgtCombo *ui;
};

#endif // WDGTCOMBO_H
