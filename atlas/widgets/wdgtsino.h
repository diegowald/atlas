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
    explicit WdgtSiNo(bool showNotes, QWidget *parent = 0);
    ~WdgtSiNo();

    bool value();
    void setValue(bool newValue);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtSiNo *ui;
};

#endif // WDGTSINO_H
