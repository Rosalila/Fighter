#include "Menu/Elemento.h"

class MenuImagen:Elemento
{
public:
    irr::video::ITexture* imagen;
    irr::video::ITexture* imagen_seleccionado;
    MenuImagen(int x, int y, int width, int height,bool visible,irr::video::ITexture* imagen);
    virtual int getTipo()
    {
        return 2;
    }
    virtual void dibujar(Grafico*grafico)
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
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)
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
};
