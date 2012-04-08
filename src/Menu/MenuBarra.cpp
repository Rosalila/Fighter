#include "Menu/MenuBarra.h"

MenuBarra::MenuBarra(Grafico*grafico,int x, int y, int width, int height,bool visible,
          irr::video::ITexture*fondo,int barra_x,int barra_y,irr::video::ITexture*barra,
          irr::video::ITexture*fondo_sel,int barra_x_sel,int barra_y_sel,irr::video::ITexture*barra_sel,
          int maximo,int actual,int accion)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;

    this->fondo=fondo;
    this->barra=barra;
    this->barra_x=barra_x;
    this->barra_y=barra_y;

    this->fondo_sel=fondo_sel;
    this->barra_sel=barra_sel;
    this->barra_x_sel=barra_x_sel;
    this->barra_y_sel=barra_y_sel;

    this->maximo=maximo;
    this->actual=actual;
    this->accion=accion;
    this->seleccionado=false;
    this->grafico=grafico;
}

int MenuBarra::getTipo()
{
    return 6;
}

void MenuBarra::avanzar()
{
    if(actual<maximo)
        actual++;
}

void MenuBarra::retroceder()
{
    if(actual>0)
        actual--;
}

void MenuBarra::dibujar()
{
    if(!seleccionado)
    {
        grafico->draw2DImage
        (   fondo,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,fondo->getOriginalSize().Width,fondo->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x,y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   barra,
            irr::core::dimension2d<irr::f32> (width*(actual/maximo),height),
            irr::core::rect<irr::f32>(0,0,barra->getOriginalSize().Width,barra->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+barra_x,y+barra_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }else
    {
        grafico->draw2DImage
        (   fondo_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,fondo_sel->getOriginalSize().Width,fondo_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x,y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   barra_sel,
            irr::core::dimension2d<irr::f32> (width*(actual/maximo),height),
            irr::core::rect<irr::f32>(0,0,barra_sel->getOriginalSize().Width,barra_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+barra_x_sel,y+barra_y_sel),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

void MenuBarra::dibujar(int alineacion_x,int alineacion_y)
{
    if(!seleccionado)
    {
        grafico->draw2DImage
        (   fondo,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,fondo->getOriginalSize().Width,fondo->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   barra,
            irr::core::dimension2d<irr::f32> (width*((float)actual/(float)maximo),height),
            irr::core::rect<irr::f32>(0,0,barra->getOriginalSize().Width*((float)actual/(float)maximo),barra->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+barra_x+alineacion_x,y+barra_y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }else
    {
        grafico->draw2DImage
        (   fondo_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,fondo_sel->getOriginalSize().Width,fondo_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   barra_sel,
            irr::core::dimension2d<irr::f32> (width*((float)actual/(float)maximo),height),
            irr::core::rect<irr::f32>(0,0,barra_sel->getOriginalSize().Width*((float)actual/(float)maximo),barra_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+barra_x_sel+alineacion_x,y+barra_y_sel+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

bool MenuBarra::getSeleccionado()
{
    return seleccionado;
}

void MenuBarra::setSeleccionado(bool seleccionado)
{
    this->seleccionado=seleccionado;
}

int MenuBarra::getAccion()
{
    return accion;
}
