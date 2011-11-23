#include "Menu/Elemento.h"

Elemento::Elemento(Grafico*grafico,int x, int y, int width, int height,bool visible)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->grafico=grafico;
}
