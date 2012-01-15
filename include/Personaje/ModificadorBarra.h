#ifndef MODIFICADORBARRA_H
#define MODIFICADORBARRA_H

#include "Personaje/Modificador.h"

class ModificadorBarra : public Modificador
{
    public:
    ModificadorBarra(stringw variable,Barra modificador,bool aplicar_a_contrario);
};

#endif
