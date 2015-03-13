#ifndef WDGTCHECKBOX_H
#define WDGTCHECKBOX_H

#include "customtooltipwidget.h"

namespace Ui {
class WdgtCheckBox;
}

class WdgtCheckBox : public CustomTooltipWidget
{
    Q_OBJECT

public:
    explicit WdgtCheckBox(QWidget *parent = 0);
    ~WdgtCheckBox();

    bool value();
    void setValue(bool newValue);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:
    void on_check_customContextMenuRequested(const QPoint &pos);

    void on_WdgtCheckBox_customContextMenuRequested(const QPoint &pos);

private:
    Ui::WdgtCheckBox *ui;
};

#endif // WDGTCHECKBOX_H
