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
    int velocity_x;
    int velocity_y;
    int initial_velocity_x;
    int initial_velocity_y;
    int acceleration_x;
    int acceleration_y;
    bool inherits_velocity;
    bool pushes;
    int separate;
    int repeat_from;
    bool land_cancelable;
    bool crouched;
    std::vector <Frame*> frames;
    Movimiento(std::string nombre,int damage,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low,int initial_velocity_x,int initial_velocity_y,int acceleration_x,int acceleration_y,bool inherits_velocity,bool pushes,int separate,int repeat_from,int land_cancelable,bool crouched,int stop_time_at,int resume_time_at,string cancel_on_hit,bool is_attack);
    ~Movimiento();
    Frame* getFrameActual();
    bool ya_pego;
    bool multihit;
    int stop_time_at;
    int resume_time_at;
    string cancel_on_hit;
    bool is_attack;
    void agregarFrame(int duracion);
    void agregarCondicion(std::vector<Condicion*> condicion,int frame);
    //void agregarCondicion(int posicion,Condicion condicion,int frame);
};

#endif
