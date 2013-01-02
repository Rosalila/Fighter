#ifndef MENUBARRA_H
#define MENUBARRA_H

#include "Menu/Elemento.h"

class MenuBarra:Elemento
{
private:
    SDL_Surface*fondo;
    SDL_Surface*barra;
    int barra_x,barra_y;
    SDL_Surface*fondo_sel;
    SDL_Surface*barra_sel;
    int barra_x_sel,barra_y_sel;
    bool seleccionado;
    int accion;
public:
    int actual;
    int maximo;
    MenuBarra(Painter*painter,int x, int y, int width, int height,bool visible,
              SDL_Surface*fondo,int barra_x,int barra_y,SDL_Surface*barra,
              SDL_Surface*fondo_sel,int barra_x_sel,int barra_y_sel,SDL_Surface*barra_sel,
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
