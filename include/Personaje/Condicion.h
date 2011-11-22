#ifndef CONDICION_H
#define CONDICION_H

class Condicion
{
public:
    stringw tipo;
    stringw variable;
    bool personaje_contrario;
    //entero
    stringw comparacion;
    int entero;
    //cadena
    stringw cadena;
    Condicion(stringw variable,stringw comparacion,int entero,bool personaje_contrario)
    {
        tipo=L"entero";
        this->variable=variable;
        this->comparacion=comparacion;
        this->entero=entero;
        this->personaje_contrario=personaje_contrario;
    }
    Condicion(stringw variable,stringw comparacion,stringw cadena,bool personaje_contrario)
    {
        tipo=L"cadena";
        this->variable=variable;
        this->comparacion=comparacion;
        this->cadena=cadena;
        this->personaje_contrario=personaje_contrario;
    }
    bool comparar(int c)
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
    bool comparar(stringw s)
    {
        if(comparacion=="=")
            return s==cadena;
        if(comparacion=="!=")
            return s!=cadena;
        return false;
    }
};

#endif
