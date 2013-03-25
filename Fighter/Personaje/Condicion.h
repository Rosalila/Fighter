#ifndef CONDICION_H
#define CONDICION_H

#include "RosalilaGraphics/RosalilaGraphics.h"

class Condicion
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
    Condicion(std::string variable,std::string comparacion,int entero,bool personaje_contrario);
    Condicion(std::string variable,std::string comparacion,std::string cadena,bool personaje_contrario);
    bool comparar(int c);
    bool comparar(std::string s);
};

#endif
