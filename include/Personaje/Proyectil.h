#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "Grafico/Grafico.h"
#include "Personaje/Imagen.h"
#include "Personaje/Frame.h"

class Proyectil
{
public:
int frame_actual,tiempo_transcurrido,damage;
    //variables
    stringw nombre;
    stringw posicion_x;
    stringw posicion_y;
    stringw imagen;
    stringw hitboxes;
    stringw estado;
    stringw orientacion;

    //logica
    vector<Imagen>sprites;
    vector <Frame> frames;
    Frame getFrameActual();
    void agregarFrame(int duracion);
    void agregarCondicion(vector<Condicion*> condicion,int frame);

    int sprite_actual;
    Proyectil(stringw nombre,stringw posicion_x,stringw posicion_y,stringw imagen,stringw hitboxes,stringw estado,stringw orientacion,vector<Imagen>sprites,int damage);
    void avanzarFrame();
};

#endif
