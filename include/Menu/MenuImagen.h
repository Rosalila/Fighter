#ifndef MENUIMAGEN_H
#define MENUIMAGEN_H

#include "Menu/Elemento.h"

class MenuImagen:Elemento
{
private:
    irr::video::ITexture* imagen;
    irr::video::ITexture* imagen_seleccionado;
public:
    stringw value;
    MenuImagen(Grafico*grafico,int x, int y, int width, int height,bool visible,irr::video::ITexture* imagen,stringw value);
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
};

#endif
