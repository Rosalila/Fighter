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
    IA(char* archivo,char* archivo_default);
    std::string getInput(irr::core::map<std::string,std::string>*strings,
                     irr::core::map<std::string,std::string>*strings_contrario,
                     irr::core::map<std::string,int>*enteros,
                     irr::core::map<std::string,int>*enteros_contrario
                     );
    void darRecompensa();
    void quitarRecompensa();
};

#endif
