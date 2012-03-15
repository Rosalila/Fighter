#ifndef MENUBOTON_H
#define MENUBOTON_H

#include "Menu/Elemento.h"

class MenuBoton:Elemento
{
private:
    bool seleccionado;
    int accion;
    irr::video::ITexture* imagen;
    stringw texto;
    video::SColor color;
    int alineacion_texto_x,alineacion_texto_y;
    irr::video::ITexture* imagen_sel;
    stringw texto_sel;
    video::SColor color_sel;
    int alineacion_texto_x_sel,alineacion_texto_y_sel;
    //otra
public:
    char* load_menu;
    stringw input_config;
    MenuBoton(Grafico*grafico,int x, int y, int width, int height,bool visible,
              irr::video::ITexture* imagen,int alineacion_texto_x,int alineacion_texto_y, stringw texto,video::SColor color,
              irr::video::ITexture* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, stringw texto_sel,video::SColor color_sel,
              int accion,char* load_menu
              );
    int getAccion();
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
    bool estaSeleccionado();
    void setSeleccionado(bool seleccionado);
};

#endif
