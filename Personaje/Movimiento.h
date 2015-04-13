#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "../Rosalila/RosalilaGraphics/RosalilaGraphics.h"
#include "Frame.h"

class Movimiento
{
    public:
    std::string nombre;
    int damage;
    int blockstun;
    int chip_damage;
    bool unblockable_low;
    bool unblockable_high;
    bool unblockable_air;
    int frame_actual,tiempo_transcurrido;
//    int velocity_x;
//    int velocity_y;
    int initial_velocity_x;
    int initial_velocity_y;
//    int acceleration_x;
//    int acceleration_y;
    int initial_acceleration_x;
    int initial_acceleration_y;
    bool inherits_velocity;
    bool pushes;
    int separate_red;
    int separate_blue;
    int repeat_from;
    bool land_cancelable;
    bool crouched;
    bool is_status;
    std::vector <Frame*> frames;
    Movimiento(std::string nombre,int damage,int blockstun,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low,int initial_velocity_x,int initial_velocity_y,int initial_acceleration_x,int initial_acceleration_y,bool inherits_velocity,bool pushes,int separate_blue,int separate_red,int repeat_from,bool land_cancelable,bool crouched,bool is_status,int stop_time_at,int resume_time_at,string cancel_on_hit,bool is_attack,bool friction,int final_velocity_x,int final_velocity_y,int final_acceleration_x,int final_acceleration_y);
    ~Movimiento();
    Frame* getFrameActual();
    bool ya_pego;
    bool multihit;
    int last_mulithit_frame_hit;
    int stop_time_at;
    int resume_time_at;
    string cancel_on_hit;
    bool is_attack;
    bool friction;
    int final_velocity_x,final_velocity_y,final_acceleration_x,final_acceleration_y;

    void agregarFrame(int duracion);
    void agregarCondicion(std::vector<Condicion*> condicion,int frame);
    void resetMove();
    //void agregarCondicion(int posicion,Condicion condicion,int frame);
};

#endif
