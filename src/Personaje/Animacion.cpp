#include "Personaje/Animacion.h"

Animacion::Animacion(stringw nombre,vector<Imagen>sprites,stringw posicion_x,stringw posicion_y,int duracion,bool personaje_contrario,bool usa_camara)
{
    this->nombre=nombre;
    this->sprites=sprites;
    this->imagen_actual=0;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->personaje_contrario=personaje_contrario;
    this->duracion=duracion;
    this->tiempo_transcurrido=0;
    this->usa_camara=usa_camara;
}
