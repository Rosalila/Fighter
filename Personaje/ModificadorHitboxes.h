#ifndef MODIFICADORHITBOXES_H
#define MODIFICADORHITBOXES_H

#include "Modificador.h"

class ModificadorHitboxes : public Modificador
{
    public:
    ModificadorHitboxes(std::string variable,std::vector <Hitbox*> modificador,bool aplicar_a_contrario);
};

#endif
