#ifndef WDGTCHECKBOX_H
#define WDGTCHECKBOX_H

#include <QWidget>

namespace Ui {
class WdgtCheckBox;
}

class WdgtCheckBox : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtCheckBox(QWidget *parent = 0);
    ~WdgtCheckBox();

private:
    Ui::WdgtCheckBox *ui;
};

#endif // WDGTCHECKBOX_H
