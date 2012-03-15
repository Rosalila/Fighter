#ifndef MENUTEXTO_H
#define MENUTEXTO_H

#include "Menu/Elemento.h"

class MenuTexto:Elemento
{
private:
    video::SColor color;
public:
    stringw texto;//!!!!!!!!
    MenuTexto(Grafico*grafico,int x, int y, int width, int height,bool visible,stringw texto,video::SColor color);
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
};

#endif
