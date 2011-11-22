#include "Personaje/Imagen.h"

Imagen::Imagen(video::ITexture* imagen,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=1;
    this->dimension_x=(int)imagen->getSize().Width;
    this->dimension_y=(int)imagen->getOriginalSize().Height;
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen(video::ITexture* imagen,float escala,int alineacion_x,int alineacion_y)
{
    this->imagen=imagen;
    this->escala=escala;
    this->dimension_x=(int)imagen->getSize().Width;
    this->dimension_y=(int)imagen->getOriginalSize().Height;
    this->alineacion_x=alineacion_x;
    this->alineacion_y=alineacion_y;
}

Imagen::Imagen()
{

}
