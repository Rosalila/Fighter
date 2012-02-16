#include "Personaje/ModificadorPorVariable.h"

ModificadorPorVariable::ModificadorPorVariable(stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    this->tipo="variable";
    this->tipo_variable=tipo;
    this->variable=variable;
    this->modificador_string=variable_modificador;
    this->relativo=relativo;
    this->aplicar_a_contrario=aplicar_a_contrario;
    this->flipeable=flipeable;
}
