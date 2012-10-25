#ifndef SONIDO_H
#define SONIDO_H

#include "../include/irrKlang/irrKlang.h"
using namespace irrklang;
#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;
#include <string>
#include <vector>
#include "Sonido/Reproduccion.h"

class Sonido
{
    ISoundEngine *engine;
    irr::core::map<stringw,Reproduccion*> sonidos;
public:
    Sonido();
    void drop();
    void agregarSonido(stringw variable,const ik_c8* valor);
    void reproducirSonido(stringw variable,bool looped);
    void pararSonido(stringw variable);
    void setVolumen(stringw variable,float volumen);
};

#endif
