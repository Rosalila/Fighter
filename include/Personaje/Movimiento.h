#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "Grafico/Grafico.h"
#include "Personaje/Frame.h"

class Movimiento
{
    public:
    stringw nombre;
    int damage;
    int frame_actual,tiempo_transcurrido;
    vector <Frame> frames;
    Movimiento(stringw nombre,int damage,bool multihit);
    Frame getFrameActual();
    bool ya_pego;
    bool multihit;
    void agregarFrame(int duracion);
    void agregarCondicion(vector<Condicion*> condicion,int frame);
    //void agregarCondicion(int posicion,Condicion condicion,int frame);
};

#endif
