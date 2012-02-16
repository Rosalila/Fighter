#ifndef BARRA_H
#define BARRA_H

#include "Grafico/Grafico.h"

class Barra
{
public:
    int tiempo;
    stringw nombre;
    stringw valor_maximo;
    stringw valor_actual;
    stringw modificador_periodico;
    stringw periodo;
    video::SColor color;
    core::rect<s32> posicion;
    irr::video::ITexture* imagen;

    Barra(){}
    Barra(stringw nombre,stringw valor_maximo,stringw valor_actual,stringw modificador_periodico,stringw periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagen);
    bool procesarTiempo(int periodo);
};

#endif
