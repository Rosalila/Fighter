#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "RosalilaGraphics/RosalilaGraphics.h"
#include "Frame.h"

class Movimiento
{
    public:
    std::string nombre;
    int damage;
    int chip_damage;
    bool unblockable_low;
    bool unblockable_high;
    bool unblockable_air;
    int frame_actual,tiempo_transcurrido;
    std::vector <Frame*> frames;
    Movimiento(std::string nombre,int damage,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low);
    ~Movimiento();
    Frame* getFrameActual();
    bool ya_pego;
    bool multihit;
    void agregarFrame(int duracion);
    void agregarCondicion(std::vector<Condicion*> condicion,int frame);
    //void agregarCondicion(int posicion,Condicion condicion,int frame);
};

#endif
