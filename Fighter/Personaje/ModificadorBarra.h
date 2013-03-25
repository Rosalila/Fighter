#ifndef MODIFICADORBARRA_H
#define MODIFICADORBARRA_H

#include "Personaje/Modificador.h"

class ModificadorBarra : public Modificador
{
    public:
    ModificadorBarra(std::string variable,Barra modificador,bool aplicar_a_contrario);
};

#endif
