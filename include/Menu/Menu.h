#include "Stage/Stage.h"
#include "Grafico/Grafico.h"
#include "irrKlang/irrKlang.h"
#include "Personaje/Personaje.h"
#include "Menu/MenuContenedor.h"
#include "Sonido/Sonido.h"
using namespace irrklang;

class Menu
{
private:
    //Engines
    Sonido* sonido;
    Grafico* grafico;
    Receiver* receiver;
    vector<Elemento*> elementos;
    MenuContenedor*contenedor_actual;
    TiXmlDocument abrirXml(char* archivo);
    void dibujarMenu();
    int pos_pa,pos_pb,pos_stage,pos_ia_lvl;

public:
    Personaje *pa,*pb;
    Stage* stage;
    Menu(Grafico* grafico,Receiver* receiver,Sonido* sonido);
    void cargarDesdeXml(char*archivo,vector<stringw> chars,vector<stringw> stages);
    void loopMenu();
    char* getPersonajeA();
    char* getPersonajeB();
    char* getStage();
};
