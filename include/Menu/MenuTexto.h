#ifndef MENUTEXTO_H
#define MENUTEXTO_H

#include "Menu/Elemento.h"

class MenuTexto:Elemento
{
private:
    //video::SColor color;//!! DRAW TEXT
public:
    std::string texto;
    MenuTexto(Painter*painter,int x, int y, int width, int height,bool visible,std::string texto);//!! DRAW TEXT color
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
};

#endif
