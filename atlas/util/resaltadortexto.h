#ifndef RESALTADORTEXTO_H
#define RESALTADORTEXTO_H

#include <QObject>
#include <QSyntaxHighlighter>

class ResaltadorTexto : public QSyntaxHighlighter
{
public:
    ResaltadorTexto(QTextDocument *parent);
    virtual ~ResaltadorTexto();

    void highlightBlock(const QString &text);
};

#endif // RESALTADORTEXTO_H
