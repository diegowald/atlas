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
    explicit WdgtCheckBox(bool showNotes, QWidget *parent = 0);
    ~WdgtCheckBox();

    bool value();
    void setValue(bool newValue);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtCheckBox *ui;
};

#endif // WDGTCHECKBOX_H
