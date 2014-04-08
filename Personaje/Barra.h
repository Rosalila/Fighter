#ifndef BARRA_H
#define BARRA_H

#include "RosalilaGraphics/RosalilaGraphics.h"

class Barra
{
public:
    int tiempo;
    std::string nombre;
    std::string valor_maximo;
    std::string valor_actual;
    std::string modificador_periodico;
    std::string periodo;
    Color color;
    bool stay_at_max;
    int pos_x1,pos_y1;
    int pos_x2,pos_y2;
    Image* imagen;

    Barra(){}
    Barra(std::string nombre,std::string valor_maximo,std::string valor_actual,std::string modificador_periodico,std::string periodo,Color color,int pos_x1,int pos_y1,int pos_x2,int pos_y2,bool stay_at_max,Image* imagen);
    bool procesarTiempo(int periodo);
};

#endif
