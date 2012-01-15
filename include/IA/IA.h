#ifndef IA_H
#define IA_H

#include "IA/Automata.h"
#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;

class IA
{
    Automata* automata;
public:
    IA();
    stringw getInput();
};

#endif
