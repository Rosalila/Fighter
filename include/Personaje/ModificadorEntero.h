#ifndef MODIFICADORENTERO_H
#define MODIFICADORENTERO_H

#include "Personaje/Modificador.h"

class ModificadorEntero : public Modificador
{
    public:
    ModificadorEntero(stringw variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
};

#endif
