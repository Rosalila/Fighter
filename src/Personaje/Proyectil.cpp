#include "Personaje/Proyectil.h"

Proyectil::Proyectil(stringw nombre,stringw posicion_x,stringw posicion_y,stringw imagen,stringw hitboxes,stringw estado,stringw orientacion)
{
    this->nombre=nombre;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->imagen=imagen;
    this->hitboxes=hitboxes;
    this->estado=estado;
    this->orientacion=orientacion;
}
