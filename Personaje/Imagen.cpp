#include "Imagen.h"

Imagen::Imagen(Image* imagen,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=1;
    this->dimension_x=(int)imagen->getWidth();
    this->dimension_y=(int)imagen->getHeight();
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen(Image* imagen,float escala,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=escala;
    this->dimension_x=(int)imagen->getWidth();
    this->dimension_y=(int)imagen->getHeight();
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen()
{

}

Imagen::~Imagen()
{
    delete imagen;
}
