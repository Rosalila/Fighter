#ifndef IMAGEN_H
#define IMAGEN_H

#include "Painter/Painter.h"

class Imagen
{
public:
    int dimension_x,dimension_y,alineacion_x,alineacion_y;
    float escala;
    Image* imagen;

    Imagen(Image* imagen,float escala,int alineacion_x,int alineacion_y);
    Imagen(Image* imagen,int alineacion_x,int alineacion_y);
    Imagen();
    ~Imagen();
};

#endif
