#ifndef TRANSICION_H
#define TRANSICION_H

#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;
#include <vector>
using namespace std;
//#include <Personaje/Condicion.h>
class Condicion2
{
private:
    //entero
    stringw comparacion;
    int entero;
    //cadena
    stringw cadena;
public:
    stringw tipo;
    bool personaje_contrario;
    stringw variable;
    Condicion2(stringw variable,stringw comparacion,int entero,bool personaje_contrario);
    Condicion2(stringw variable,stringw comparacion,stringw cadena,bool personaje_contrario);
    bool comparar(int c);
    bool comparar(stringw s);
};


class Transicion
{
    stringw input;
    stringw destino;
    int recompensa;
    int wait;
    vector<Condicion2>condiciones;
public:
    bool recompensable;
    Transicion(stringw input,stringw destino,bool recompensable);
    void agregarCondicion(Condicion2 condicion);
    void setRecompensa(int recomensa);
    void setWait(int wait);
    stringw getInput();
    stringw getDestino();
    int getRecompensa();
    int getWait();
    bool cumpleCondiciones(irr::core::map<stringw,stringw>*strings,irr::core::map<stringw,stringw>*strings_contrario);
    bool cumpleCondicion(Condicion2 condicion,irr::core::map<stringw,stringw>*strings,irr::core::map<stringw,stringw>*strings_contrario);
};

#endif
