#ifndef MENUBOTON_H
#define MENUBOTON_H

#include "Menu/Elemento.h"

class MenuBoton:Elemento
{
private:
    bool seleccionado;
    int accion;
    SDL_Surface* imagen;
    std::string texto;
    int alineacion_texto_x,alineacion_texto_y;
    SDL_Surface* imagen_sel;
    std::string texto_sel;
    int alineacion_texto_x_sel,alineacion_texto_y_sel;
    //otra
public:
    char* load_menu;
    std::string input_config;
    MenuBoton(Painter*painter,int x, int y, int width, int height,bool visible,
              SDL_Surface* imagen,int alineacion_texto_x,int alineacion_texto_y, std::string texto,
              SDL_Surface* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, std::string texto_sel,
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
