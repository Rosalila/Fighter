#include "Personaje/Barra.h"

Barra::Barra(std::string nombre, std::string valor_maximo,std::string valor_actual,std::string modificador_periodico,std::string periodo,Color color,core::rect<s32> posicion,Image* imagen)
{
    this->tiempo=0;
    this->nombre=nombre;
    this->valor_maximo=valor_maximo;
    this->valor_actual=valor_actual;
    this->modificador_periodico=modificador_periodico;
    this->periodo=periodo;
    this->color=color;
    this->posicion=posicion;
    this->imagen=imagen;
}

bool Barra::procesarTiempo(int periodo)
{
    if(tiempo<periodo)
    {
        tiempo++;
        return false;
    }
    tiempo=0;
    return true;
}
