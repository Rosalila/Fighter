#ifndef PALETA_H
#define PALETA_H

#include <vector>
#include "TinyXml/tinyxml.h"
#include "Painter/Painter.h"

class CambioColor
{
public:
    Color color_max;
    Color color_min;
    int cambio_a,cambio_r,cambio_g,cambio_b;
    CambioColor(Color color_max,Color color_min,
                int cambio_a,int cambio_r,int cambio_g,int cambio_b)
                {
                    this->color_max=color_max;
                    this->color_min=color_min;
                    this->cambio_a=cambio_a;
                    this->cambio_r=cambio_r;
                    this->cambio_g=cambio_g;
                    this->cambio_b=cambio_b;
                }
};

class Paleta
{
public:
    std::vector<CambioColor>cambios;
//    s32 *copia;
    Paleta(){}
    void cargarXML(char* archivo,int num_paleta);
    Image* paintTexture(Image* texture);
    Image* restoreTexture(Image* texture);
};

#endif
