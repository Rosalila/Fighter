#ifndef TRANSICION_H
#define TRANSICION_H

#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;

class Transicion
{
    stringw input;
    stringw destino;
public:
    Transicion(stringw input,stringw destino);
    stringw getInput();
    stringw getDestino();
};

#endif
