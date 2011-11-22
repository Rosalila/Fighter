#ifndef MODIFICADORSTRING_H
#define MODIFICADORSTRING_H

#include "Personaje/Modificador.h"

class ModificadorString : public Modificador
{
    public:
    ModificadorString(stringw variable,stringw modificador,bool aplicar_a_contrario);
};

#endif
