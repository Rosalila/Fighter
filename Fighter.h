#ifndef FIGHTER_H
#define FIGHTER_H

#include "Rosalila/TinyXml/tinyxml.h"
#include "FighterMenu/FighterMenu.h"
#include <stdio.h>

class Menu;

class Fighter
{
public:
    //Logica
    Menu* pause_menu;
    Stage* stage;
    int px_colision,py_colision;
    std::map<char,Image*>input_buffer_images;
    std::vector<Personaje*>pa;
    std::vector<Personaje*>pb;
    int pa_vivos,pb_vivos;
    int pa_actual,pb_actual;
    std::vector<Imagen*>ko;
    int pos_imagen_ko,duracion_ko,tiempo_actual_ko;
    std::vector<Imagen*>match_intro;
    int pos_imagen_intro,duracion_intro,tiempo_actual_intro;
    bool game_over_a;
    bool game_over_b;
    int victories_a;
    int victories_b;
    std::string move_cancel_pa;
    std::string move_cancel_pb;
    bool stop_time_pa;
    bool stop_time_pb;

    //hit cancel control
    std::string hit_cancel_pa;
    int hit_cancel_pa_damage;
    int hit_cancel_pa_chip_damage;
    bool hit_cancel_pa_unblockable_air;
    bool hit_cancel_pa_unblockable_high;
    bool hit_cancel_pa_unblockable_low;
    std::string hit_cancel_pb;
    int hit_cancel_pb_damage;
    int hit_cancel_pb_chip_damage;
    bool hit_cancel_pb_unblockable_air;
    bool hit_cancel_pb_unblockable_high;
    bool hit_cancel_pb_unblockable_low;
    int victory_image_x;
    int victory_image_y;

    //Engines
    Sound* sonido;
    RosalilaGraphics* painter;
    Receiver* receiver;

    //Misc
    Image* texture_bar;
    Image* texture_victory;

    Fighter(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,vector<Personaje*>pa,vector<Personaje*>pb,Stage*stage,int victories_a,int victories_b);
    ~Fighter();
    //Logica
    bool getColisionHitBoxes(HitBox* hb_azul,HitBox* hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,std::string variable_atacante,Personaje* atacado,std::string variable_atacado);
    void loopJuego();
    void logicaPersonaje(Personaje *p);
    void landCancel(Personaje *p);
    void colisionCheck(Personaje*p);
    void cancel(Personaje *p);
    void logicaStage();
    void aplicarModificadores(Personaje *p);
    void mandatoryModifiers(Personaje* p,Movimiento* m);
    void velocityInheritance(Personaje* p, Movimiento* old_move, Movimiento* new_move);
    void logica();
    void printHitboxes();
    void printBuffer();
    void render();
    void dibujarBarra();
    Personaje* getPaActual();
    Personaje* getPbActual();
    Personaje* get2doPa();
    Personaje* get2doPb();
    Personaje* get3erPa();
    Personaje* get3erPb();
    void setPaActual(Personaje* p);
    void setPbActual(Personaje* p);
};

#endif
