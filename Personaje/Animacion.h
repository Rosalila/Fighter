#ifndef ANIMACION_H
#define ANIMACION_H

#include <vector>
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "Imagen.h"

class Animacion
{
public:
    std::string nombre;
    std::vector<Imagen*>sprites;
    int duracion,tiempo_transcurrido;
    int imagen_actual;
    std::string posicion_x,posicion_y;
    bool personaje_contrario;
    bool usa_camara;
    Animacion(std::string nombre,std::vector<Imagen*>sprites,std::string posicion_x,std::string posicion_y,int duracion,bool personaje_contrario,bool usa_camara);
    ~Animacion();
};

#endif
