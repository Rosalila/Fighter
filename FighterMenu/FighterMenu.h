#ifndef MENUTEST_H
#define MENUTEST_H

#include "../Rosalila/system.h"
#include "../Stage/Stage.h"
#include "../Rosalila/RosalilaGraphics/RosalilaGraphics.h"
#include "../Personaje/Personaje.h"
#include "../Rosalila/RosalilaMenus/MenuContenedor.h"
#include "../Rosalila/RosalilaMenus/MenuCharSelect.h"
#include "../Rosalila/RosalilaMenus/MenuGallery.h"
#include "../Rosalila/RosalilaSound/RosalilaSound.h"
#include "../Fighter.h"
#include "GameplayEditor.h"
#include "InputEditor.h"

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
    GameplayEditor gameplay_editor;
    InputEditor input_editor;

    int player1_wins_count;
    int player2_wins_count;

    bool config_button_lock;

    void iniciarJuego(int num_personajes,bool inteligencia_artificial,bool is_training);
public:
    std::string music_path;
    RosalilaInputs *input_player1,*input_player2;
    bool keyup_player1,keyup_player2;
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
    void editInputCheck();
    void keyboardPressedEditInput(string button,int player);
    void reloadInputs();
    void applyGraphicEffects();
    void updateKeyUpCheck();
    void renderGallery();
    void characterSelectControl();
};

#endif
