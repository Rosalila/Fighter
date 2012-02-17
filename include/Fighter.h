#include "TinyXml/tinyxml.h"
#include "Menu/Menu.h"
#include <stdio.h>

class Fighter
{
public:
    //Logica
    Input*inputa,*inputb;
    Menu *menu,*pause_menu;
    Stage* stage;
    int pos_stage;
    Personaje *pa;
    Personaje *pb;

    //Engines
    Sonido* sonido;
    Grafico* grafico;
    Receiver* receiver;

    Fighter();
    //Logica
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,stringw variable_atacante,Personaje* atacado,stringw variable_atacado);
    bool getColisionHitBoxes(Personaje*atacante,stringw variable_atacante,Personaje*atacado,stringw variable_atacado,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    void loopJuego();
    void logicaPersonaje(Personaje *p);
    void logicaStage();
    void logicaStagePersonaje(Personaje *p);
    void aplicarModificadores(Personaje *p);
    void logica();
    bool render(Personaje* pa,Personaje* pb,Stage* stage);
    void mainLoop();
    void escribirInputsXML();
};
