#ifndef AUTOMATA_H
#define AUTOMATA_H


#include "IA/Estado.h"
#include "TinyXml/tinyxml.h"
#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;
#include <vector>
using namespace std;

class Automata
{
    irr::core::map<stringw,Estado*> estados;
    stringw estado_actual;
    int wait;
public:
Transicion *transicion_a_recompenzar;
    Automata();
    Estado* getEstadoInicial();
    stringw getNextInput(irr::core::map<stringw,stringw>*strings,irr::core::map<stringw,stringw>*strings_contrario);
    void cargarDesdeXML(char* archivo);
};

#endif
