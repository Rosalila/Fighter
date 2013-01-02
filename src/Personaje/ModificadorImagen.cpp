#include "Personaje/ModificadorImagen.h"

ModificadorImagen::ModificadorImagen(std::string variable,Imagen modificador,bool aplicar_a_contrario)
{
    tipo="imagen";
    this->variable=variable;
    this->modificador_imagen=modificador;
    this->aplicar_a_contrario=aplicar_a_contrario;
}
