#ifndef ESTADO_H
#define ESTADO_H

#include "IA/Transicion.h"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
#include "IA/Estado.h"
#include <irrlicht/irrlicht.h>

class Estado
{
public:
    std::vector<Transicion*>transiciones;
    Estado(vector<Transicion*>transiciones);
    Transicion* getNextTransicion(irr::core::map<std::string,std::string>*strings,
                                  irr::core::map<std::string,std::string>*strings_contrario,
                                  irr::core::map<std::string,int>*enteros,
                                  irr::core::map<std::string,int>*enteros_contrario
                                  );
};

#endif
