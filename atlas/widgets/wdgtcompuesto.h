#ifndef WDGTCOMPUESTO_H
#define WDGTCOMPUESTO_H

#include <QWidget>
#include "../model/forward.h"

namespace Ui {
class WdgtCompuesto;
}

class WdgtCompuesto : public QWidget
{
    Q_OBJECT

public:
    explicit WdgtCompuesto(bool showNotes, QWidget *parent = 0);
    ~WdgtCompuesto();

    void setLabel(const QString &label);
    void addPregunta(PreguntaBasePtr pregunta);
    void setChecked(bool checked);
    bool isChecked() const;
    void setNotes(const QString &newNote);
    QString notes() const;

private slots:

private:
    Ui::WdgtCompuesto *ui;
};

#endif // WDGTCOMPUESTO_H
