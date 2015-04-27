#include "resaltadortexto.h"

ResaltadorTexto::ResaltadorTexto(QTextDocument *parent) : QSyntaxHighlighter(parent)
{

}

ResaltadorTexto::~ResaltadorTexto()
{

}

void ResaltadorTexto::highlightBlock(const QString &text)
{

    enum { NormalState = -1, CStyleRed,
           CStyleGreen, CStyleBlue,
           CStyleBold, CStyleUnderline };

    int state = previousBlockState();
    int start = 0;

    for (int i = 0; i < text.length(); ++i)
    {
        /*
         /*- Rojo
         /*+ Verde
         /*. Azul
         /*= Negrita
         /*_ Subrayado
        */
        if (state != NormalState)
        {
            if (text.mid(i, 2) == "*/")
            {
                switch (state)
                {
                case CStyleRed:
                    setFormat(start, i - start + 2, Qt::red);
                    break;
                case CStyleGreen:
                    setFormat(start, i - start + 2, Qt::green);
                    break;
                case CStyleBlue:
                    setFormat(start, i - start + 2, Qt::blue);
                    break;
                case CStyleBold:
                {
                    QFont font = format(start).font();
                    font.setBold(true);
                    setFormat(start, i - start +2, font);
                    break;
                }
                case CStyleUnderline:
                {
                    QFont font = format(start).font();
                    font.setUnderline(true);
                    setFormat(start, i - start +2, font);
                    break;
                }
                case NormalState:
                default:
                {
                    QFont font = format(start).font();
                    font.setUnderline(false);
                    font.setBold(false);
                    setFormat(start, i - start +2, font);
                    setFormat(start, i - start + 2, Qt::black);
                    break;
                }
                }
                state = NormalState;

            }
        }
        else
        {
            if (text.mid(i, 2) == "//")
            {
                setFormat(i, text.length() - i, Qt::red);
                break;
            }
            else if (text.mid(i, 3) == "/*-")
            {
                start = i;
                state = CStyleRed;
            }
            else if (text.mid(i, 3) == "/*+")
            {
                start = i;
                state = CStyleGreen;
            }
            else if (text.mid(i, 3) == "/*.")
            {
                start = i;
                state = CStyleBlue;
            }
            else if (text.mid(i, 3) == "/*=")
            {
                start = i;
                state = CStyleBold;
            }
            else if (text.mid(i, 3) == "/*_")
            {
                start = i;
                state = CStyleUnderline;
            }
        }
    }
}
