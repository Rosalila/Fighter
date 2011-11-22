#ifndef MODIFICADORIMAGEN_H
#define MODIFICADORIMAGEN_H

#include "Personaje/Modificador.h"

class ModificadorImagen : public Modificador
{
    public:
    ModificadorImagen(stringw variable,Imagen modificador,bool aplicar_a_contrario);
};

#endif
