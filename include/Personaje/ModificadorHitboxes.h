#ifndef MODIFICADORHITBOXES_H
#define MODIFICADORHITBOXES_H

#include "Personaje/Modificador.h"

class ModificadorHitboxes : public Modificador
{
    public:
    ModificadorHitboxes(stringw variable,vector <HitBox> modificador,bool aplicar_a_contrario);
};

#endif
