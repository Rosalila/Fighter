#include "Menu/MenuBoton.h"

MenuBoton::MenuBoton(Grafico*grafico,int x, int y, int width, int height,bool visible,
          irr::video::ITexture* imagen,int alineacion_texto_x,int alineacion_texto_y, stringw texto,video::SColor color,
          irr::video::ITexture* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, stringw texto_sel,video::SColor color_sel,
          int accion,char* load_menu
          )
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->imagen=imagen;
    this->texto=texto;
    this->color=color;
    this->alineacion_texto_x=alineacion_texto_x;
    this->alineacion_texto_y=alineacion_texto_y;
    this->imagen_sel=imagen_sel;
    this->texto_sel=texto_sel;
    this->color_sel=color_sel;
    this->alineacion_texto_x_sel=alineacion_texto_x_sel;
    this->alineacion_texto_y_sel=alineacion_texto_y_sel;
    this->seleccionado=false;
    this->accion=accion;
    this->load_menu=load_menu;
    this->grafico=grafico;
    this->input_config="not set";
}

int MenuBoton::getAccion()
{
    return accion;
}

int MenuBoton::getTipo()
{
    return 4;
}

void MenuBoton::dibujar()
{
    if(!seleccionado)
    {
        grafico->draw2DImage
        (   imagen,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x,y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);

        stringw temp=texto;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        grafico->drawText(temp,core::rect<s32>(x+alineacion_texto_x,y+alineacion_texto_y,x+width,y+height),color);
    }else
    {
        grafico->draw2DImage
        (   imagen_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,imagen_sel->getOriginalSize().Width,imagen_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x,y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);

        stringw temp=texto_sel;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        grafico->drawText(temp,core::rect<s32>(x+alineacion_texto_x_sel,y+alineacion_texto_y_sel,x+width,y+height),color_sel);
    }
}

void MenuBoton::dibujar(int alineacion_x,int alineacion_y)
{
    if(!seleccionado)
    {
        grafico->draw2DImage
        (   imagen,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);

        stringw temp=texto;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        grafico->drawText(temp,core::rect<s32>(x+alineacion_texto_x+alineacion_x,y+alineacion_texto_y+alineacion_y,x+width,y+height),color);
    }else
    {
        grafico->draw2DImage
        (   imagen_sel,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,imagen_sel->getOriginalSize().Width,imagen_sel->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (1,1),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);

        stringw temp=texto_sel;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        grafico->drawText(temp,core::rect<s32>(x+alineacion_texto_x_sel+alineacion_x,y+alineacion_texto_y_sel+alineacion_y,x+width,y+height),color_sel);
    }
}

bool MenuBoton::estaSeleccionado()
{
    return seleccionado;
}

void MenuBoton::setSeleccionado(bool seleccionado)
{
    this->seleccionado=seleccionado;
}
