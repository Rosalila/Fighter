#ifndef CONDICION_H
#define CONDICION_H

#include "Grafico/Grafico.h"

class Condicion
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
    Condicion(stringw variable,stringw comparacion,int entero,bool personaje_contrario);
    Condicion(stringw variable,stringw comparacion,stringw cadena,bool personaje_contrario);
    bool comparar(int c);
    bool comparar(stringw s);
};

#endif
