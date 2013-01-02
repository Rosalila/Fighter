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
    irr::core::map<std::string,Estado*> estados;
    std::string estado_actual;
    int wait;
public:
Transicion *transicion_a_recompenzar;
    Automata(char* archivo,char* archivo_default);
    Estado* getEstadoInicial();
    std::string getNextInput(irr::core::map<std::string,std::string>*strings,
                         irr::core::map<std::string,std::string>*strings_contrario,
                         irr::core::map<std::string,int>*enteros,
                         irr::core::map<std::string,int>*enteros_contrario
                         );
    void cargarDesdeXML(char* archivo,char* archivo_default);
};

#endif
