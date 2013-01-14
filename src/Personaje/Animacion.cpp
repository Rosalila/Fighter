#include "Personaje/Animacion.h"

Animacion::Animacion(std::string nombre,std::vector<Imagen*>sprites,std::string posicion_x,std::string posicion_y,int duracion,bool personaje_contrario,bool usa_camara)
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
