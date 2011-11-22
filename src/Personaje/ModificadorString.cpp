#include "Personaje/ModificadorString.h"

ModificadorString::ModificadorString(stringw variable,stringw modificador,bool aplicar_a_contrario)
{
    tipo="string";
    this->variable=variable;
    this->modificador_string=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
