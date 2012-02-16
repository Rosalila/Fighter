#include "Personaje/Barra.h"

Barra::Barra(stringw nombre, stringw valor_maximo,stringw valor_actual,stringw modificador_periodico,stringw periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagen)
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
