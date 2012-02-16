#ifndef MODIFICADORPORVARIABLE_H
#define MODIFICADORPORVARIABLE_H

#include "Personaje/Modificador.h"

class ModificadorPorVariable : public Modificador
{
    public:
    ModificadorPorVariable(stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
};

#endif
