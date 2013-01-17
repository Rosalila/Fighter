#include "Personaje/Movimiento.h"

Movimiento::Movimiento(std::string nombre,int damage,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low)
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
