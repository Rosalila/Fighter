#include "Movimiento.h"

Movimiento::Movimiento(std::string nombre,int damage,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low,int velocity_x,int velocity_y,int acceleration_x,int acceleration_y)
{
    frame_actual=0;
    tiempo_transcurrido=0;
    this->nombre=nombre;
    this->damage=damage;
    this->chip_damage=chip_damage;
    this->ya_pego=false;
    this->multihit=multihit;
    this->unblockable_air=unblockable_air;
    this->unblockable_high=unblockable_high;
    this->unblockable_low=unblockable_low;
    this->velocity_x=velocity_x;
    this->velocity_y=velocity_y;
    this->acceleration_x=acceleration_x;
    this->acceleration_y=acceleration_y;
}

Movimiento::~Movimiento()
{
    for(;!frames.empty();)
    {
        Frame*frame=frames.back();
        frames.pop_back();
        delete frame;
    }
}

Frame* Movimiento::getFrameActual()
{
    return frames[frame_actual];
}
void Movimiento::agregarFrame(int duracion)
{
    frames.push_back(new Frame(duracion));
}

void Movimiento::agregarCondicion(std::vector<Condicion*> condicion,int frame)
{
    frames[frame]->condiciones.push_back(condicion);
}

//void Movimiento::agregarCondicion(int posicion,Condicion condicion,int frame)
//{
//    frames[frame].condiciones[posicion].push_back(condicion);
//}
