#ifndef ESTADO_H
#define ESTADO_H

#include "IA/Transicion.h"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
#include "IA/Estado.h"
#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;

class Estado
{
    vector<Transicion*>transiciones;
public:
    Estado(vector<Transicion*>transiciones);
    Transicion* getNextTransicion();
};

#endif
