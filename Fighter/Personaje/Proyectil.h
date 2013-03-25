#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "RosalilaGraphics/RosalilaGraphics.h"
#include "Personaje/Imagen.h"
#include "Personaje/Frame.h"

class Proyectil
{
public:
int frame_actual,tiempo_transcurrido,damage;
    //variables
    std::string nombre;
    std::string posicion_x;
    std::string posicion_y;
    std::string imagen;
    std::string hitboxes;
    std::string estado;
    std::string orientacion;
    bool multihit;

    //logica
    std::vector<Imagen*>sprites;
    std::vector <Frame*> frames;
    Frame* getFrameActual();
    void agregarFrame(int duracion);
    void agregarCondicion(std::vector<Condicion*> condicion,int frame);

    int sprite_actual;
    Proyectil(std::string nombre,std::string posicion_x,std::string posicion_y,std::string imagen,std::string hitboxes,std::string estado,std::string orientacion,std::vector<Imagen*>sprites,int damage,bool multihit);
    void avanzarFrame();
};

#endif
