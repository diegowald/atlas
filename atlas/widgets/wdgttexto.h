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
    explicit WdgtTexto(bool showNotes, QWidget *parent = 0);
    ~WdgtTexto();

    QString value();
    void setValue(const QString &value);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtTexto *ui;
};

#endif // WDGTTEXTO_H
