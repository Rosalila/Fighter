#ifndef MENUBARRA_H
#define MENUBARRA_H

#include "Menu/Elemento.h"

class MenuBarra:Elemento
{
private:
    irr::video::ITexture*fondo;
    irr::video::ITexture*barra;
    int barra_x,barra_y;
    irr::video::ITexture*fondo_sel;
    irr::video::ITexture*barra_sel;
    int barra_x_sel,barra_y_sel;
    bool seleccionado;
    int accion;
public:
    int actual;
    int maximo;
    MenuBarra(Grafico*grafico,int x, int y, int width, int height,bool visible,
              irr::video::ITexture*fondo,int barra_x,int barra_y,irr::video::ITexture*barra,
              irr::video::ITexture*fondo_sel,int barra_x_sel,int barra_y_sel,irr::video::ITexture*barra_sel,
              int maximo,int actual,int accion);
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
    void avanzar();
    void retroceder();
    bool getSeleccionado();
    void setSeleccionado(bool seleccionado);
    int getAccion();
};

#endif
