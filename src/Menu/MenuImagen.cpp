#include "Menu/MenuImagen.h"

MenuImagen::MenuImagen(int x, int y, int width, int height,bool visible,irr::video::ITexture* imagen)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->imagen=imagen;
}
