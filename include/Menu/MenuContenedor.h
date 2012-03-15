#ifndef MENUCONTENEDOR_H
#define MENUCONTENEDOR_H

#include "Menu/Elemento.h"
#include "Menu/MenuLista.h"
#include "Menu/MenuBarra.h"
#include "Menu/MenuBoton.h"
#include "Menu/MenuImagen.h"
#include "Menu/MenuTexto.h"

class MenuContenedor:Elemento
{
private:
    int seleccionado;
public:
    vector<Elemento*> elementos;//!!!!!!!
    MenuContenedor(Grafico*grafico,int x, int y, int width, int height,bool visible,vector<Elemento*> elementos);
    virtual int getTipo();
    virtual void dibujar();
    virtual void dibujar(int alineacion_x,int alineacion_y);
    void avanzar();
    void retroceder();
    Elemento* getElementoSeleccionado();
};

#endif
