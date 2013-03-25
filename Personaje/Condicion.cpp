#include "Personaje/Condicion.h"

Condicion::Condicion(std::string variable,std::string comparacion,int entero,bool personaje_contrario)
{
    tipo="entero";
    this->variable=variable;
    this->comparacion=comparacion;
    this->entero=entero;
    this->personaje_contrario=personaje_contrario;
}

Condicion::Condicion(std::string variable,std::string comparacion,std::string cadena,bool personaje_contrario)
{
    tipo="cadena";
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

bool Condicion::comparar(std::string s)
{
    if(comparacion=="=")
        return s==cadena;
    if(comparacion=="!=")
        return s!=cadena;
    return false;
}
