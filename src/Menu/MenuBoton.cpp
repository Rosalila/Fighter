#include "Menu/MenuBoton.h"

MenuBoton::MenuBoton(Painter*painter,int x, int y, int width, int height,bool visible,
          SDL_Surface* imagen,int alineacion_texto_x,int alineacion_texto_y, std::string texto,
          SDL_Surface* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, std::string texto_sel,
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
    this->alineacion_texto_x=alineacion_texto_x;
    this->alineacion_texto_y=alineacion_texto_y;
    this->imagen_sel=imagen_sel;
    this->texto_sel=texto_sel;
    this->alineacion_texto_x_sel=alineacion_texto_x_sel;
    this->alineacion_texto_y_sel=alineacion_texto_y_sel;
    this->seleccionado=false;
    this->accion=accion;
    this->load_menu=load_menu;
    this->painter=painter;
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
        painter->draw2DImage
        (   imagen,
            width,height,
            x,y,
            0,
            false);

        std::string temp=texto;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        //painter->drawText(temp,core::rect<s32>(x+alineacion_texto_x,y+alineacion_texto_y,x+width,y+height),color);//!!DRAW TEXT
    }else
    {
        painter->draw2DImage
        (   imagen_sel,
            width,height,
            x,y,
            0,
            false);

        std::string temp=texto_sel;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        //painter->drawText(temp,core::rect<s32>(x+alineacion_texto_x_sel,y+alineacion_texto_y_sel,x+width,y+height),color_sel);//!!DRAW TEXT
    }
}

void MenuBoton::dibujar(int alineacion_x,int alineacion_y)
{
    if(!seleccionado)
    {
        painter->draw2DImage
        (   imagen,
            width,height,
            x+alineacion_x,y+alineacion_y,
            0,
            false);

        std::string temp=texto;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        //painter->drawText(temp,core::rect<s32>(x+alineacion_texto_x+alineacion_x,y+alineacion_texto_y+alineacion_y,x+width,y+height),color);//!!DRAW TEXT
    }else
    {
        painter->draw2DImage
        (   imagen_sel,
            width,height,
            x+alineacion_x,y+alineacion_y,
            0,
            false);

        std::string temp=texto_sel;
        if(accion>=10 && accion<=29)
        {
            temp+=input_config;
        }
        //painter->drawText(temp,core::rect<s32>(x+alineacion_texto_x_sel+alineacion_x,y+alineacion_texto_y_sel+alineacion_y,x+width,y+height),color_sel);//!!DRAW TEXT
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
