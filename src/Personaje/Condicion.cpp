#include "Personaje/Condicion.h"

Condicion::Condicion(stringw variable,stringw comparacion,int entero,bool personaje_contrario)
{
    tipo=L"entero";
    this->variable=variable;
    this->comparacion=comparacion;
    this->entero=entero;
    this->personaje_contrario=personaje_contrario;
}

Condicion::Condicion(stringw variable,stringw comparacion,stringw cadena,bool personaje_contrario)
{
    tipo=L"cadena";
    this->variable=variable;
    this->comparacion=comparacion;
    this->cadena=cadena;
    this->personaje_contrario=personaje_contrario;
}

bool Condicion::comparar(int c)
{
    //cout<<comparacion.c_str()[0]<<endl;cout.flush();
    if(comparacion=="=")
        return c==entero;
    if(comparacion=="!=")
        return c!=entero;
    if(comparacion=="<")
        return c<entero;
    if(comparacion==">")
        return c>entero;
    if(comparacion=="<=")
        return c<=entero;
    if(comparacion==">=")
        return c>=entero;
    return false;
}

bool Condicion::comparar(stringw s)
{
    if(comparacion=="=")
        return s==cadena;
    if(comparacion=="!=")
        return s!=cadena;
    return false;
}
