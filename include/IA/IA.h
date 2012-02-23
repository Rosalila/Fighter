#ifndef IA_H
#define IA_H

#include "IA/Automata.h"
#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;
#include <cstdlib>
#include <iostream>
using namespace std;

class IA
{
    Automata *automata;
public:
    Transicion *transicion_a_recompenzar;
    IA(char* archivo);
    stringw getInput(irr::core::map<stringw,stringw>*strings,
                     irr::core::map<stringw,stringw>*strings_contrario,
                     irr::core::map<stringw,int>*enteros,
                     irr::core::map<stringw,int>*enteros_contrario
                     );
    void darRecompensa();
    void quitarRecompensa();
};

#endif
