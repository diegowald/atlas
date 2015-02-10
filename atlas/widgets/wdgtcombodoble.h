#ifndef WDGTCOMBODOBLE_H
#define WDGTCOMBODOBLE_H

#include <QWidget>

namespace Ui {
class WdgtComboDoble;
}

class WdgtComboDoble : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtComboDoble(QWidget *parent = 0);
    ~WdgtComboDoble();

private:
    Ui::WdgtComboDoble *ui;
};

#endif // WDGTCOMBODOBLE_H
