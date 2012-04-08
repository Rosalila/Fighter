#include "Menu/MenuLista.h"

MenuLista::MenuLista(Grafico*grafico,int x, int y, int width, int height,bool visible,
          int flecha_izq_x,int flecha_izq_y,irr::video::ITexture*flecha_izquierda,int flecha_der_x,int flecha_der_y,irr::video::ITexture*flecha_derecha,
          int flecha_izq_x_sel,int flecha_izq_y_sel,irr::video::ITexture*flecha_izquierda_sel,int flecha_der_x_sel,int flecha_der_y_sel,irr::video::ITexture*flecha_derecha_sel,
          vector<Elemento*>elementos,int accion
          )
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;

    this->flecha_izq_x=flecha_izq_x;
    this->flecha_izq_y=flecha_izq_y;
    this->flecha_izquierda=flecha_izquierda;
    this->flecha_der_x=flecha_der_x;
    this->flecha_der_y=flecha_der_y;
    this->flecha_derecha=flecha_derecha;

    this->flecha_izq_x_sel=flecha_izq_x_sel;
    this->flecha_izq_y_sel=flecha_izq_y_sel;
    this->flecha_izquierda_sel=flecha_izquierda_sel;
    this->flecha_der_x_sel=flecha_der_x_sel;
    this->flecha_der_y_sel=flecha_der_y_sel;
    this->flecha_derecha_sel=flecha_derecha_sel;

    this->elementos=elementos;
    actual=0;
    this->accion=accion;
    seleccionado=false;
    this->grafico=grafico;
}

int MenuLista::getTipo()
{
    return 5;
}

void MenuLista::avanzar()
{
    if(actual<(int)elementos.size()-1)
        actual++;
}

void MenuLista::retroceder()
{
    if(actual>0)
        actual--;
}

void MenuLista::dibujar()
{
    if(!seleccionado)
    {
        if(actual>=0 && actual<(int)elementos.size())
            elementos[actual]->dibujar(x,y);
        grafico->draw2DImage
        (   flecha_izquierda,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_izquierda->getOriginalSize().Width,flecha_izquierda->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_izq_x,y+flecha_izq_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   flecha_derecha,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_derecha->getOriginalSize().Width,flecha_derecha->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_der_x,y+flecha_der_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }else
    {
        if(actual>=0 && actual<(int)elementos.size())
            elementos[actual]->dibujar(x,y);
        grafico->draw2DImage
        (   flecha_izquierda_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_izquierda_sel->getOriginalSize().Width,flecha_izquierda_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_izq_x_sel,y+flecha_izq_y_sel),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   flecha_derecha_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_derecha_sel->getOriginalSize().Width,flecha_derecha_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_der_x_sel,y+flecha_der_y_sel),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

void MenuLista::dibujar(int alineacion_x,int alineacion_y)
{
    if(!seleccionado)
    {
        if(actual>=0 && actual<(int)elementos.size())
            elementos[actual]->dibujar(x+alineacion_x,y+alineacion_y);
        grafico->draw2DImage
        (   flecha_izquierda,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_izquierda->getOriginalSize().Width,flecha_izquierda->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_izq_x+alineacion_x,y+flecha_izq_y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   flecha_derecha,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_derecha->getOriginalSize().Width,flecha_derecha->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_der_x+alineacion_x,y+flecha_der_y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }else
    {
        if(actual>=0 && actual<(int)elementos.size())
            elementos[actual]->dibujar(x+alineacion_x,y+alineacion_y);
        grafico->draw2DImage
        (   flecha_izquierda_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_izquierda_sel->getOriginalSize().Width,flecha_izquierda_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_izq_x_sel+alineacion_x,y+flecha_izq_y_sel+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
        grafico->draw2DImage
        (   flecha_derecha_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,flecha_derecha_sel->getOriginalSize().Width,flecha_derecha_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+flecha_der_x_sel+alineacion_x,y+flecha_der_y_sel+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
}

bool MenuLista::estaSeleccionado()
{
    return seleccionado;
}

void MenuLista::setSeleccionado(bool seleccionado)
{
    this->seleccionado=seleccionado;
}

int MenuLista::getAccion()
{
    return accion;
}

Elemento* MenuLista::getElementoActual()
{
    return elementos[actual];
}
