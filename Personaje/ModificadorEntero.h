#ifndef MODIFICADORENTERO_H
#define MODIFICADORENTERO_H

#include "Modificador.h"

class ModificadorEntero : public Modificador
{
    public:
    ModificadorEntero(std::string variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
};

#endif
