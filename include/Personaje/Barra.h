#ifndef BARRA_H
#define BARRA_H

#include "Grafico/Grafico.h"

class Barra
{
public:
    stringw valor_maximo;
    stringw valor_actual;
    stringw modificador_periodico;
    stringw periodo;
    video::SColor color;
    core::rect<s32> posicion;
    irr::video::ITexture* imagenes[];

    Barra(stringw valor_maximo,stringw valor_actual,stringw modificador_periodico,stringw periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagenes[]);
    Barra(){}
};

#endif
