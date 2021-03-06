#ifndef WDGTWITHLABEL_H
#define WDGTWITHLABEL_H

#include <QWidget>

namespace Ui {
class WdgtWithLabel;
}

class WdgtWithLabel : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtWithLabel(bool showNotes, QWidget *parent = 0);
    ~WdgtWithLabel();
    void addWidget(const QString &label, QWidget* widget);
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtWithLabel *ui;
};

#endif // WDGTWITHLABEL_H
