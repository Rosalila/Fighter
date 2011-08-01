#include "../include/Menu.h"
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
    Input* receiver;
    Fighter(Stage* stage,Personaje*pa,Personaje*pb,Input *receiver,Grafico *grafico,Sonido *sonido);
    //Logica
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,Personaje* atacado);
    void logica(Personaje*personaje,stringw input);
    void loopJuego();
    bool render(Personaje* pa,Personaje* pb,Stage* stage);
};
