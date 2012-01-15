#include "IA/Transicion.h"

Transicion::Transicion(stringw input,stringw destino)
{
    this->input=input;
    this->destino=destino;
}

stringw Transicion::getInput()
{
    return input;
}

stringw Transicion::getDestino()
{
    return destino;
}
