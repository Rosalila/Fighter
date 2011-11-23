#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "Grafico/Grafico.h"

class Elemento
{
protected:
    Grafico*grafico;
public:
    int x;
    int y;
    int width;
    int height;
    bool visible;
    Elemento(){}
    Elemento(Grafico*grafico,int x, int y, int width, int height,bool visible);
    virtual void dibujar()=0;
    virtual void dibujar(int alineacion_x,int alineacion_y)=0;
    virtual int getTipo()=0;
};
#endif
