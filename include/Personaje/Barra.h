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
    Color color;
    core::rect<s32> posicion;
    Image* imagen;

    Barra(){}
    Barra(std::string nombre,std::string valor_maximo,std::string valor_actual,std::string modificador_periodico,std::string periodo,Color color,core::rect<s32> posicion,Image* imagen);
    bool procesarTiempo(int periodo);
};

#endif
