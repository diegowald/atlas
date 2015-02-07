#ifndef WIDGETPREGUNTA_H
#define WIDGETPREGUNTA_H

#include <QWidget>

namespace Ui {
class WidgetPregunta;
}

class WidgetPregunta : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPregunta(QWidget *parent = 0);
    ~WidgetPregunta();

private:
    void popupMenu(QWidget *widget);

private slots:
    void on_newNote(bool checked);
private:
    Ui::WidgetPregunta *ui;
    QWidget *_overWidget;
};

#endif // WIDGETPREGUNTA_H
