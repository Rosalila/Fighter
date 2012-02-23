#include "IA/Transicion.h"

Transicion::Transicion(stringw input,stringw destino,bool recompensable)
{
    this->input=input;
    this->destino=destino;
    this->recompensable=recompensable;
    this->recompensa=0;
    this->wait=0;
}

void Transicion::agregarCondicion(Condicion2 condicion)
{
    condiciones.push_back(condicion);
}

void Transicion::setRecompensa(int recompensa)
{
    this->recompensa=recompensa;
}

void Transicion::setWait(int wait)
{
    this->wait=wait;
}

stringw Transicion::getInput()
{
    return input;
}

stringw Transicion::getDestino()
{
    return destino;
}

int Transicion::getWait()
{
    return wait;
}

int Transicion::getRecompensa()
{
    return recompensa;
}

bool Transicion::cumpleCondiciones(irr::core::map<stringw,stringw>*strings,
                                   irr::core::map<stringw,stringw>*strings_contrario,
                                   irr::core::map<stringw,int>*enteros,
                                   irr::core::map<stringw,int>*enteros_contrario
                                   )
{
    for(int i=0;i<(int)condiciones.size();i++)
    {
        if(condiciones[i].tipo=="cadena")
        {
            if(!cumpleCondicion(condiciones[i],strings,strings_contrario))
                return false;
        }else
        {
            if(!cumpleCondicion(condiciones[i],enteros,enteros_contrario))
                return false;
        }
    }
    return true;
}

bool Transicion::cumpleCondicion(Condicion2 condicion,irr::core::map<stringw,stringw>*strings,irr::core::map<stringw,stringw>*strings_contrario)
{
    if(condicion.personaje_contrario)
        return condicion.comparar(strings_contrario->operator[](condicion.variable));
    return condicion.comparar(strings->operator[](condicion.variable));
}

bool Transicion::cumpleCondicion(Condicion2 condicion,irr::core::map<stringw,int>*enteros,irr::core::map<stringw,int>*enteros_contrario)
{
    if(condicion.personaje_contrario)
        return condicion.comparar(enteros_contrario->operator[](condicion.variable));
    return condicion.comparar(enteros->operator[](condicion.variable));
}


///////////////////////////////////////////////7


Condicion2::Condicion2(stringw variable,stringw comparacion,int entero,bool personaje_contrario)
{
    tipo=L"entero";
    this->variable=variable;
    this->comparacion=comparacion;
    this->entero=entero;
    this->personaje_contrario=personaje_contrario;
}

Condicion2::Condicion2(stringw variable,stringw comparacion,stringw cadena,bool personaje_contrario)
{
    tipo=L"cadena";
    this->variable=variable;
    this->comparacion=comparacion;
    this->cadena=cadena;
    this->personaje_contrario=personaje_contrario;
}

bool Condicion2::comparar(int c)
{
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

bool Condicion2::comparar(stringw s)
{
    if(comparacion=="=")
        return s==cadena;
    if(comparacion=="!=")
        return s!=cadena;
    return false;
}
