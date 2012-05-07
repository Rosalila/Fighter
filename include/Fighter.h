#ifndef FIGHTER_H
#define FIGHTER_H

#include "TinyXml/tinyxml.h"
#include "Menu/Menu.h"
#include <stdio.h>

class Menu;

class Fighter
{
public:
    //Logica
    Input*inputa,*inputb;
    Menu* pause_menu;
    Stage* stage;
    int pos_stage;
    int px_colision,py_colision;
    vector<Personaje*>pa;
    vector<Personaje*>pb;
    int pa_vivos,pb_vivos;
    int pa_actual,pb_actual;
    vector<Imagen>ko;
    int pos_imagen_ko,duracion_ko,tiempo_actual_ko;
    vector<Imagen>match_intro;
    int pos_imagen_intro,duracion_intro,tiempo_actual_intro;
    bool game_over_a;
    bool game_over_b;

    //Engines
    Sonido* sonido;
    Grafico* grafico;
    Receiver* receiver;

    Fighter(Sonido* sonido,Grafico* grafico,Receiver* receiver,vector<Personaje*>pa,vector<Personaje*>pb,Stage*stage);
    ~Fighter();
    //Logica
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,stringw variable_atacante,Personaje* atacado,stringw variable_atacado);
    bool getColisionHitBoxes(Personaje*atacante,stringw variable_atacante,Personaje*atacado,stringw variable_atacado,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    void loopJuego();
    void logicaPersonaje(Personaje *p);
    void logicaStage();
    void aplicarModificadores(Personaje *p);
    void logica();
    bool render();
    void dibujarBarra();
    void escribirInputsXML();
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
