#include "Personaje/Proyectil.h"

Proyectil::Proyectil(std::string nombre,std::string posicion_x,std::string posicion_y,std::string imagen,std::string hitboxes,std::string estado,std::string orientacion,std::vector<Imagen*>sprites,int damage,bool multihit)
{
    this->nombre=nombre;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->imagen=imagen;
    this->hitboxes=hitboxes;
    this->estado=estado;
    this->orientacion=orientacion;
    this->sprites=sprites;
    this->frame_actual=0;
    this->tiempo_transcurrido=0;
    this->sprite_actual=0;
    this->damage=damage;
    this->multihit=multihit;
}

void Proyectil::avanzarFrame()
{
    frame_actual++;
    sprite_actual++;
    if(sprite_actual>=(int)sprites.size())
        sprite_actual=0;
}

Frame* Proyectil::getFrameActual()
{
    return frames[frame_actual];
}
void Proyectil::agregarFrame(int duracion)
{
    frames.push_back(new Frame(duracion));
}

void Proyectil::agregarCondicion(std::vector<Condicion*> condicion,int frame)
{
    frames[frame]->condiciones.push_back(condicion);
}
