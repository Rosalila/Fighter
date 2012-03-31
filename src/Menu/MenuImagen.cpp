#include "Menu/MenuImagen.h"

MenuImagen::MenuImagen(Grafico*grafico,int x, int y, int width, int height,bool visible,irr::video::ITexture* imagen,stringw value)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->imagen=imagen;
    this->grafico=grafico;
    this->value=value;
}

int MenuImagen::getTipo()
{
    return 2;
}

void MenuImagen::dibujar()
{
    grafico->draw2DImage
    (   imagen,
        irr::core::dimension2d<irr::f32> (width,height),
        irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
        irr::core::position2d<irr::f32>(x,y),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (0,0),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);
}

void MenuImagen::dibujar(int alineacion_x,int alineacion_y)
{
    grafico->draw2DImage
    (   imagen,
        irr::core::dimension2d<irr::f32> (width,height),
        irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
        irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (0,0),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);
}
