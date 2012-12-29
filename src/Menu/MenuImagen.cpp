#include "Menu/MenuImagen.h"

MenuImagen::MenuImagen(Painter*painter,int x, int y, int displacement_x, int displacement_y,int stop_displacement_x_at,int stop_displacement_y_at, int fade_in_initial,int fade_in_speed, int width, int height,bool visible,irr::video::ITexture* imagen,irr::video::ITexture* original_image,stringw value)
{
    this->x=x;
    this->y=y;
    this->displacement_x=displacement_x;
    this->displacement_y=displacement_y;
    this->stop_displacement_x_at=stop_displacement_x_at;
    this->stop_displacement_y_at=stop_displacement_y_at;
    this->fade_in_current=fade_in_initial;
    this->fade_in_speed=fade_in_speed;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->imagen=imagen;
    this->original_image=original_image;
    this->painter=painter;
    this->value=value;
}

int MenuImagen::getTipo()
{
    return 2;
}

void MenuImagen::dibujar()
{
    painter->draw2DImage
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
    painter->draw2DImage
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
