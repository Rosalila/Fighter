#ifndef TRANSICION_H
#define TRANSICION_H

#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;
#include <vector>
#include <iostream>
using namespace std;
//#include <Personaje/Condicion.h>
class Condicion2
{
private:
    //entero
    std::string comparacion;
    int entero;
    //cadena
    std::string cadena;
public:
    std::string tipo;
    bool personaje_contrario;
    std::string variable;
    Condicion2(std::string variable,std::string comparacion,int entero,bool personaje_contrario);
    Condicion2(std::string variable,std::string comparacion,std::string cadena,bool personaje_contrario);
    bool comparar(int c);
    bool comparar(std::string s);
};


class Transicion
{
    std::string input;
    std::string destino;
    int recompensa;
    int wait;
    std::vector<Condicion2>condiciones;
public:
    bool recompensable;
    Transicion(std::string input,std::string destino,bool recompensable);
    void agregarCondicion(Condicion2 condicion);
    void setRecompensa(int recomensa);
    void setWait(int wait);
    std::string getInput();
    std::string getDestino();
    int getRecompensa();
    int getWait();
    bool cumpleCondiciones(irr::core::map<std::string,std::string>*strings,
                           irr::core::map<std::string,std::string>*strings_contrario,
                           irr::core::map<std::string,int>*enteros,
                           irr::core::map<std::string,int>*enteros_contrario
                           );
    bool cumpleCondicion(Condicion2 condicion,irr::core::map<std::string,std::string>*strings,irr::core::map<std::string,std::string>*strings_contrario);
    bool cumpleCondicion(Condicion2 condicion,irr::core::map<std::string,int>*enteros,irr::core::map<std::string,int>*enteros_contrario);
};

#endif
