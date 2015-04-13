#include "Movimiento.h"

Movimiento::Movimiento(std::string nombre,int damage, int blockstun,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low,int initial_velocity_x,int initial_velocity_y,int initial_acceleration_x,int initial_acceleration_y,bool inherits_velocity, bool pushes,int separate_blue, int separate_red,int repeat_from,bool land_cancelable,bool crouched,bool is_status,int stop_time_at,int resume_time_at,string cancel_on_hit,bool is_attack,bool friction,int final_velocity_x,int final_velocity_y,int final_acceleration_x,int final_acceleration_y)
{
    frame_actual=0;
    tiempo_transcurrido=0;
    this->nombre=nombre;
    this->damage=damage;
    this->blockstun=blockstun;
    this->chip_damage=chip_damage;
    this->ya_pego=false;
    this->multihit=multihit;
    last_mulithit_frame_hit=-1;
    this->unblockable_air=unblockable_air;
    this->unblockable_high=unblockable_high;
    this->unblockable_low=unblockable_low;
//    this->velocity_x=initial_velocity_x;
//    this->velocity_y=initial_velocity_y;
    this->initial_velocity_x=initial_velocity_x;
    this->initial_velocity_y=initial_velocity_y;
//    this->acceleration_x=initial_acceleration_x;
//    this->acceleration_y=initial_acceleration_y;
    this->initial_acceleration_x=initial_acceleration_x;
    this->initial_acceleration_y=initial_acceleration_y;
    this->inherits_velocity=inherits_velocity;
    this->pushes=pushes;
    this->separate_red=separate_red;
    this->separate_blue=separate_blue;
    this->repeat_from=repeat_from;
    this->land_cancelable=land_cancelable;
    this->crouched=crouched;
    this->is_status=is_status;
    this->stop_time_at=stop_time_at;
    this->resume_time_at=resume_time_at;
    this->cancel_on_hit=cancel_on_hit;
    this->is_attack=is_attack;
    this->friction=friction;
    this->final_velocity_x=final_velocity_x;
    this->final_velocity_y=final_velocity_y;
    this->final_acceleration_x=final_acceleration_x;
    this->final_acceleration_y=final_acceleration_y;
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

void Movimiento::resetMove()
{
    frame_actual=0;
    tiempo_transcurrido=0;
    ya_pego=false;
    last_mulithit_frame_hit=-1;
}
