#ifndef COLORIZEDTEXTEDIT_H
#define COLORIZEDTEXTEDIT_H

#include <QTextEdit>
#include <QAction>

class ColorizedTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    ColorizedTextEdit(QWidget *parent = 0);
    ~ColorizedTextEdit();

public slots:
    void onRojoTriggered();
    void onVerdeTriggered();
    void onAzulTriggered();
    void onNegritaTriggered();
    void onSubrayarTriggered();

protected:
    virtual void contextMenuEvent(QContextMenuEvent *e);

    void replaceText(const QString &startMark, const QString &endMark);
private:
    QAction *_rojoAction;
    QAction *_verdeAction;
    QAction *_azulAction;
    QAction *_negritaAction;
    QAction *_subrayarAction;
};

#endif // COLORIZEDTEXTEDIT_H
