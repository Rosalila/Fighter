#ifndef MENUTEST_H
#define MENUTEST_H

#include "../Stage/Stage.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "../Personaje/Personaje.h"
#include "RosalilaMenus/MenuContenedor.h"
#include "RosalilaMenus/MenuCharSelect.h"
#include "RosalilaSound/RosalilaSound.h"
#include "../Fighter.h"

class Menu
{
private:
    //Engines
    Sound* sonido;
    RosalilaGraphics* painter;
    Receiver* receiver;
    std::vector<Elemento*> elementos;
    MenuContenedor*selectables_container;
    TiXmlDocument abrirXml(char* archivo);
    void dibujarMenu();
//    std::vector<int> pos_pa;
//    std::vector<int> pos_pb;
    int pos_stage,pos_ia_lvl;
    bool exit_signal,save_inputs_signal;
    MenuCharSelect* char_select;

    //config vars
    int ai_level,time,rounds;

    void iniciarJuego(int num_personajes,bool inteligencia_artificial);
public:
    std::string music_path;
    RosalilaInputs *inputa,*inputb;
    std::vector<Personaje*>pa;
    std::vector<Personaje*>pb;
    Stage* stage;

    //Misc
    Image* vs_screen;

    Menu(){}
    Menu(RosalilaGraphics* painter,Receiver* receiver,Sound* sonido,std::string archivo);
    void cargarDesdeXml(std::string archivo,vector<std::string> chars,vector<std::string> stages);
    void cargarConfig();
    void loopMenu();
    Personaje* getPersonajeA(int num,bool ia);
    Personaje* getPersonajeB(int num,bool ia);
    std::string getStage();
    bool getExitSignal();
    bool getSaveRosalilaInputssSignal();
    void escribirRosalilaInputssXML(RosalilaInputs* ia,RosalilaInputs* ib);
    std::string getRosalilaInputsPressed();
    void llenarInputsBotones();
    int toKeyCode(std::string str);
    void printVsScreen(vector<Image*>pa_previews,vector<Image*>pb_previews);
};

#endif
