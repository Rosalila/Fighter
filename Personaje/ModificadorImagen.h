#ifndef MODIFICADORIMAGEN_H
#define MODIFICADORIMAGEN_H

#include "Modificador.h"

class ModificadorImagen : public Modificador
{
    public:
    ModificadorImagen(std::string variable,Imagen* modificador,bool aplicar_a_contrario);
};

#endif
