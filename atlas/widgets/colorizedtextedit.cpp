#include "colorizedtextedit.h"

#include <QMenu>
#include <QContextMenuEvent>
#include "util/resaltadortexto.h"

ColorizedTextEdit::ColorizedTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    _rojoAction = new QAction(QString("Rojo"), this);
    _verdeAction = new QAction(QString("Verde"), this);
    _azulAction = new QAction(QString("Azul"), this);
    _negritaAction = new QAction(QString("Negrita"), this);
    _subrayarAction = new QAction(QString("Subrayado"), this);

    connect(_rojoAction, SIGNAL(triggered()), this, SLOT(onRojoTriggered()));
    connect(_verdeAction, SIGNAL(triggered()), this, SLOT(onVerdeTriggered()));
    connect(_azulAction, SIGNAL(triggered()), this, SLOT(onAzulTriggered()));
    connect(_negritaAction, SIGNAL(triggered()), this, SLOT(onNegritaTriggered()));
    connect(_subrayarAction, SIGNAL(triggered()), this, SLOT(onSubrayarTriggered()));

    ResaltadorTexto *_resaltador = new ResaltadorTexto(document());
}

ColorizedTextEdit::~ColorizedTextEdit()
{

}

void ColorizedTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu *menu = createStandardContextMenu();
    if (0 < textCursor().selectedText().length())
    {
        menu->addSeparator();
        QList<QAction*> actions;
        actions << _rojoAction << _azulAction << _verdeAction << _negritaAction << _subrayarAction;
        menu->addActions(actions);
    }
    menu->exec(mapToGlobal(e->pos()));
    delete menu;
}

void ColorizedTextEdit::onRojoTriggered()
{
    QString startMark = "/*-";
    QString endMark = "*/";
    replaceText(startMark, endMark);
}

void ColorizedTextEdit::onVerdeTriggered()
{
    QString startMark = "/*+";
    QString endMark = "*/";
    replaceText(startMark, endMark);
}

void ColorizedTextEdit::onAzulTriggered()
{
    QString startMark = "/*.";
    QString endMark = "*/";
    replaceText(startMark, endMark);
}

void ColorizedTextEdit::onNegritaTriggered()
{
    QString startMark = "/*=";
    QString endMark = "*/";
    replaceText(startMark, endMark);
}

void ColorizedTextEdit::onSubrayarTriggered()
{
    QString startMark = "/*_";
    QString endMark = "*/";
    replaceText(startMark, endMark);
}

void ColorizedTextEdit::replaceText(const QString &startMark, const QString &endMark)
{
    QString texto = textCursor().selectedText();
    texto = startMark + texto + endMark;
    textCursor().insertText(texto);
}
