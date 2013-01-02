#include "Personaje/Imagen.h"

Imagen::Imagen(SDL_Surface* imagen,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=1;
    this->dimension_x=(int)imagen->w;
    this->dimension_y=(int)imagen->h;
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen(SDL_Surface* imagen,float escala,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=escala;
    this->dimension_x=(int)imagen->w;
    this->dimension_y=(int)imagen->h;
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen()
{

}
