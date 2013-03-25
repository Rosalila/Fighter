#include "ModificadorString.h"

ModificadorString::ModificadorString(std::string variable,std::string modificador,bool aplicar_a_contrario)
{
    tipo="string";
    this->variable=variable;
    this->modificador_string=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
