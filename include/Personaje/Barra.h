#ifndef BARRA_H
#define BARRA_H

#include "Painter/Painter.h"

#include <irrlicht/irrlicht.h>
using namespace irr;

class Barra
{
public:
    int tiempo;
    std::string nombre;
    std::string valor_maximo;
    std::string valor_actual;
    std::string modificador_periodico;
    std::string periodo;
    video::SColor color;
    core::rect<s32> posicion;
    SDL_Surface* imagen;

    Barra(){}
    Barra(std::string nombre,std::string valor_maximo,std::string valor_actual,std::string modificador_periodico,std::string periodo,video::SColor color,core::rect<s32> posicion,SDL_Surface* imagen);
    bool procesarTiempo(int periodo);
};

#endif
