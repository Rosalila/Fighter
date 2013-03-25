#include "ModificadorPorVariable.h"

ModificadorPorVariable::ModificadorPorVariable(std::string tipo,std::string variable,std::string variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    this->tipo="variable";
    this->tipo_variable=tipo;
    this->variable=variable;
    this->modificador_string=variable_modificador;
    this->relativo=relativo;
    this->aplicar_a_contrario=aplicar_a_contrario;
    this->flipeable=flipeable;
}
