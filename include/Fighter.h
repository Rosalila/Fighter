#include "../include/Menu.h"
#include <stdio.h>

class Fighter
{
public:
    //Logica
    Stage* stage;
    Personaje *pa;
    Personaje *pb;

    //Engines
    Sonido* sonido;
    Grafico* grafico;

    Fighter(Stage* stage,Personaje*pa,Personaje*pb,Grafico *grafico,Sonido *sonido);
    //Logica
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,stringw variable_atacante,Personaje* atacado,stringw variable_atacado);
    void loopJuego();
    void logicaPersonaje(Personaje *p);
    void aplicarModificadores(Personaje *p);
    void logica();
    bool render(Personaje* pa,Personaje* pb,Stage* stage);
};
