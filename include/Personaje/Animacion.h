#ifndef ANIMACION_H
#define ANIMACION_H

#include "Grafico/Grafico.h"
#include "Personaje/Imagen.h"

class Animacion
{
public:
    stringw nombre;
    vector<Imagen>sprites;
    int duracion,tiempo_transcurrido;
    int imagen_actual;
    stringw posicion_x,posicion_y;
    bool personaje_contrario;
    bool usa_camara;
    Animacion(stringw nombre,vector<Imagen>sprites,stringw posicion_x,stringw posicion_y,int duracion,bool personaje_contrario,bool usa_camara);
};

#endif
