#include "IA/Estado.h"

Estado::Estado(vector<Transicion*>transiciones)
{
    this->transiciones=transiciones;
}

Transicion* Estado::getNextTransicion()
{
    if(transiciones.size()==0)
        return new Transicion("5","S");
    int r=std::rand()%transiciones.size();
    return transiciones[r];
}
