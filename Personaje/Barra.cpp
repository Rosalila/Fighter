#include "Barra.h"

Barra::Barra(std::string nombre, std::string valor_maximo,std::string valor_actual,std::string modificador_periodico,std::string periodo,Color color,int pos_x1,int pos_y1,int pos_x2,int pos_y2,bool stay_at_max,Image* imagen)
{
    this->tiempo=0;
    this->nombre=nombre;
    this->valor_maximo=valor_maximo;
    this->valor_actual=valor_actual;
    this->modificador_periodico=modificador_periodico;
    this->periodo=periodo;
    this->color=color;
    this->pos_x1=pos_x1;
    this->pos_y1=pos_y1;
    this->pos_x2=pos_x2;
    this->pos_y2=pos_y2;
    this->stay_at_max=stay_at_max;
    this->imagen=imagen;
}

bool Barra::procesarTiempo(int periodo)
{
    if(tiempo<periodo)
    {
        tiempo++;
        return false;
    }
    tiempo=0;
    return true;
}
