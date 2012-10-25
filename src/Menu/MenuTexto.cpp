#include "Menu/MenuTexto.h"

MenuTexto::MenuTexto(Painter*painter,int x, int y, int width, int height,bool visible,stringw texto,video::SColor color)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->texto=texto;
    this->color=color;
    this->painter=painter;
}

int MenuTexto::getTipo()
{
    return 3;
}

void MenuTexto::dibujar()
{
    painter->drawText(texto,core::rect<s32>(x,y,x+width,y+height),color);
}

void MenuTexto::dibujar(int alineacion_x,int alineacion_y)
{
    painter->drawText(texto,core::rect<s32>(x+alineacion_x,y+alineacion_y,x+width,y+height),color);
}
