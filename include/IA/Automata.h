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
public:
    Automata();
    Estado* getEstadoInicial();
    stringw getNextInput();
    void cargarDesdeXML(char* archivo);
};

#endif
