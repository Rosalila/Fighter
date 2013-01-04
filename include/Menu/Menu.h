#ifndef MENUTEST_H
#define MENUTEST_H

#include "Stage/Stage.h"
#include "Painter/Painter.h"
#include "irrKlang/irrKlang.h"
#include "Personaje/Personaje.h"
#include "Menu/MenuContenedor.h"
#include "Menu/MenuCharSelect.h"
#include "Sonido/Sonido.h"
#include "Fighter.h"
using namespace irrklang;


class Menu
{
private:
    //Engines
    Sonido* sonido;
    Painter* painter;
    Receiver* receiver;
    std::vector<Elemento*> elementos;
    MenuContenedor*contenedor_actual;
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
    Input *inputa,*inputb;
    std::vector<Personaje*>pa;
    std::vector<Personaje*>pb;
    Stage* stage;

    //Misc
    LTexture* vs_screen;

    Menu(){}
    Menu(Painter* painter,Receiver* receiver,Sonido* sonido,char* archivo);
    void cargarDesdeXml(char*archivo,vector<std::string> chars,vector<std::string> stages);
    void cargarConfig();
    void loopMenu();
    Personaje* getPersonajeA(int num,bool ia);
    Personaje* getPersonajeB(int num,bool ia);
    char* getStage();
    bool getExitSignal();
    bool getSaveInputsSignal();
    void escribirInputsXML(Input* ia,Input* ib);
    std::string getInputPressed();
    void llenarInputsBotones();
    irr::EKEY_CODE toKeyCode(std::string str);
    void printVsScreen(vector<LTexture*>pa_previews,vector<LTexture*>pb_previews);
};

#endif
