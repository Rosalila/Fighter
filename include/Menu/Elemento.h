#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "Grafico/Grafico.h"

class Elemento
{
public:
    int x;
    int y;
    int height;
    int width;
    bool visible;
    Elemento(){}
    Elemento(int x, int y, int width, int height,bool visible);
    virtual void dibujar(Grafico*grafico)=0;
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)=0;
    virtual int getTipo()=0;
};
#endif
