#include "Personaje/ModificadorEntero.h"

ModificadorEntero::ModificadorEntero(stringw variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    tipo="entero";
    this->variable=variable;
    this->modificador_entero=modificador;
    this->relativo=relativo;
    this->aplicar_a_contrario=aplicar_a_contrario;
    this->flipeable=flipeable;
}
