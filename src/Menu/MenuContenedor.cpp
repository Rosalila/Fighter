#include "Menu/MenuContenedor.h"

MenuContenedor::MenuContenedor(Grafico*grafico,int x, int y, int width, int height,bool visible,vector<Elemento*> elementos)
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->visible=visible;
    this->elementos=elementos;
    this->seleccionado=0;
    for(int i=0;i<(int)elementos.size();i++)
        if(elementos[i]->getTipo()==4 || elementos[i]->getTipo()==5 || elementos[i]->getTipo()==6)
        {
            if(elementos[i]->getTipo()==4)
                ((MenuBoton*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()==5)
                ((MenuLista*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()==6)
                ((MenuBarra*)elementos[i])->setSeleccionado(true);
            seleccionado=i;
            break;
        }
    this->grafico=grafico;
}

int MenuContenedor::getTipo()
{
    return 1;
}

void MenuContenedor::dibujar()
{
    for(int i=0;i<(int)elementos.size();i++)
        elementos[i]->dibujar(x,y);
}

void MenuContenedor::dibujar(int alineacion_x,int alineacion_y)
{
    for(int i=0;i<(int)elementos.size();i++)
        elementos[i]->dibujar(x+alineacion_x,y+alineacion_y);
}

void MenuContenedor::avanzar()
{
    for(int i=seleccionado+1;i<(int)elementos.size();i++)
        if(elementos[i]->getTipo()==4 || elementos[i]->getTipo()==5 || elementos[i]->getTipo()==6)
        {
            if(elementos[seleccionado]->getTipo()==4)
                ((MenuBoton*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()==5)
                ((MenuLista*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()==6)
                ((MenuBarra*)elementos[seleccionado])->setSeleccionado(false);

            if(elementos[i]->getTipo()==4)
                ((MenuBoton*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()==5)
                ((MenuLista*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()==6)
                ((MenuBarra*)elementos[i])->setSeleccionado(true);
            seleccionado=i;
            break;
        }
}

void MenuContenedor::retroceder()
{
    for(int i=seleccionado-1;i>=0;i--)
        if(elementos[i]->getTipo()==4 || elementos[i]->getTipo()==5 || elementos[i]->getTipo()==6)
        {
            if(elementos[seleccionado]->getTipo()==4)
                ((MenuBoton*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()==5)
                ((MenuLista*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()==6)
                ((MenuBarra*)elementos[seleccionado])->setSeleccionado(false);

            if(elementos[i]->getTipo()==4)
                ((MenuBoton*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()==5)
                ((MenuLista*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()==6)
                ((MenuBarra*)elementos[i])->setSeleccionado(true);
            seleccionado=i;
            break;
        }
}

Elemento* MenuContenedor::getElementoSeleccionado()
{
    return elementos[seleccionado];
}
