#ifndef WDGTSINO_H
#define WDGTSINO_H

#include <QWidget>

namespace Ui {
class WdgtSiNo;
}

class WdgtSiNo : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtSiNo(QWidget *parent = 0);
    ~WdgtSiNo();

private:
    Ui::WdgtSiNo *ui;
};

#endif // WDGTSINO_H
