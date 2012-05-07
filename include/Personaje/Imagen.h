#ifndef IMAGEN_H
#define IMAGEN_H

#include "Grafico/Grafico.h"

class Imagen
{
public:
    int dimension_x,dimension_y,alineacion_x,alineacion_y;
    float escala;
    video::ITexture* imagen;

    Imagen(video::ITexture* imagen,float escala,int alineacion_x,int alineacion_y);
    Imagen(video::ITexture* imagen,int alineacion_x,int alineacion_y);
    Imagen();
};

#endif
