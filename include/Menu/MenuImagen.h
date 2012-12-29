#ifndef MENUIMAGEN_H
#define MENUIMAGEN_H

#include "Menu/Elemento.h"

class MenuImagen:Elemento
{
private:
public:
    int fade_in_current;
    int fade_in_speed;
    irr::video::ITexture* imagen;
    irr::video::ITexture* original_image;
    irr::video::ITexture* imagen_seleccionado;
    stringw value;
    MenuImagen(Painter*painter,int x, int y, int displacement_x, int displacement_y,int stop_displacement_x_at,int stop_displacement_y_at,int fade_in_current,int fade_in_speed,int width, int height,bool visible,irr::video::ITexture* imagen,irr::video::ITexture* original_image,stringw value);
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
};

#endif
