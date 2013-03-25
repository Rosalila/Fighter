#ifndef MODIFICADORSTRING_H
#define MODIFICADORSTRING_H

#include "Personaje/Modificador.h"

class ModificadorString : public Modificador
{
    public:
    ModificadorString(std::string variable,std::string modificador,bool aplicar_a_contrario);
};

#endif
