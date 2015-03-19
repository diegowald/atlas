#ifndef FORWARD
#define FORWARD

#include <QSharedPointer>

#define CONSTRUCT(X) \
    class X; \
    typedef QSharedPointer<X> X## Ptr;

CONSTRUCT(HistoriaClinica)
CONSTRUCT(Persona)
CONSTRUCT(PreguntaBase)
CONSTRUCT(PreguntaCheckBox)
CONSTRUCT(PreguntaCombo)
CONSTRUCT(PreguntaComboDoble)
CONSTRUCT(PreguntaCompuesta)
CONSTRUCT(PreguntaSiNo)
CONSTRUCT(PreguntaTexto)
CONSTRUCT(Alarma)
#endif // FORWARD

