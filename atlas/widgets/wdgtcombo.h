#ifndef WDGTCOMBO_H
#define WDGTCOMBO_H

#include <QWidget>

namespace Ui {
class WdgtCombo;
}

class WdgtCombo : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtCombo(QWidget *parent = 0);
    ~WdgtCombo();

private:
    Ui::WdgtCombo *ui;
};

#endif // WDGTCOMBO_H
