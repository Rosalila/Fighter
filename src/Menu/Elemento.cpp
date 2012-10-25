#include "Menu/Elemento.h"

Elemento::Elemento(Painter*painter,int x, int y, int width, int height,bool visible)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->painter=painter;
}
