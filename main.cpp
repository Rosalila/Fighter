#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "include/Input.h"
#include "include/Fighter.h"

#include"include/Parser.h"

void wizardAgregarImagenes(Personaje* personaje,stringw carpeta,int frames,stringw movimiento,Grafico *grafico)
{
    for(int i=0;i<frames;i++)
    {
        stringw s;
        std::stringstream out;
        out << (i+1);
        irr::core::stringw outw(out.str().c_str());
        s = carpeta+outw+".png";
        irr::core::stringw str(s.c_str());
        personaje->agregarModificador(movimiento,i,Imagen(grafico->getTexture(irr::io::path(str)),3,0,0),"imagen_personaje",false);
    }
}

class Ryu : Personaje
{
public:
    Ryu(Barra hp,int px,int py,int a,stringw orientacion,Grafico* grafico,Personaje *personaje_contrario,Input* input)
    {
        stringw carpeta="resources/Personajes/RyuSF2";
        vector <HitBox> hb_roja,hb_azul;
        this->input=input;
        setImagen("imagen_personaje",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/stand/idle/1.png"),1,100,100));

        this->grafico=grafico;
        setString("estado_posicion","");
        setString("saltando_lock","");
        setString("recibir_lock","");
        setString("orientacion",orientacion);
        setString("movimiento_actual","5");
        setString("movimiento_actual_continuo","");
        setString("colision_hitboxes","");

        setEntero("hp_valor_maximo",250);
        setEntero("hp_valor_actual",250);
        setEntero("hp_modificador_periodico",-1);
        setEntero("hp_periodo",1);

        enteros["posicion_x"]=px;
        enteros["posicion_y"]=py;

        barras["hp"]=hp;

        vector<HitBox> hb_vacia;
        hitboxes["azules"]=hb_vacia;
        hitboxes["rojas"]=hb_vacia;

        vector<Condicion> condicion;
        vector<stringw> lista_input;

        //especiales
        agregarMovimiento("tatsumaki");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("4");
        lista_input.push_back("4d");
        agregarInput(lista_input,"tatsumaki");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("4");
        lista_input.push_back("4e");
        agregarInput(lista_input,"tatsumaki");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("4");
        lista_input.push_back("4f");
        agregarInput(lista_input,"tatsumaki");
        for(int i=0;i<8;i++)
            agregarFrame("tatsumaki",3);
        for(int i=0;i<8;i++)
            agregarModificador("tatsumaki",i,5,"posicion_x",true,false);
        agregarModificador("tatsumaki",0,-10,"posicion_y",true,false);
        agregarModificador("tatsumaki",7,10,"posicion_y",true,false);
        wizardAgregarImagenes(this,carpeta+"/special/tatsumaki/",8,"tatsumaki",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("tatsumaki",0,condicion);

        agregarMovimiento("shoryuken");
        lista_input.clear();
        lista_input.push_back("6");
        lista_input.push_back("2");
        lista_input.push_back("3a");
        agregarInput(lista_input,"shoryuken");
        lista_input.clear();
        lista_input.push_back("6");
        lista_input.push_back("2");
        lista_input.push_back("3b");
        agregarInput(lista_input,"shoryuken");
        lista_input.clear();
        lista_input.push_back("6");
        lista_input.push_back("2");
        lista_input.push_back("3c");
        agregarInput(lista_input,"shoryuken");
        for(int i=0;i<7;i++)
            agregarFrame("shoryuken",3);
        agregarModificador("shoryuken",3,-10,"posicion_y",true,false);
        agregarModificador("shoryuken",4,-10,"posicion_y",true,false);
        agregarModificador("shoryuken",5,10,"posicion_y",true,false);
        agregarModificador("shoryuken",6,10,"posicion_y",true,false);
        wizardAgregarImagenes(this,carpeta+"/special/shoryuken/",7,"shoryuken",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("shoryuken",0,condicion);

        agregarMovimiento("hadouken");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("6");
        lista_input.push_back("6a");
        agregarInput(lista_input,"hadouken");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("6");
        lista_input.push_back("6b");
        agregarInput(lista_input,"hadouken");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("6");
        lista_input.push_back("6c");
        agregarInput(lista_input,"hadouken");
        for(int i=0;i<5;i++)
            agregarFrame("hadouken",3);
        wizardAgregarImagenes(this,carpeta+"/special/hadouken/",5,"hadouken",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("hadouken",0,condicion);

        agregarMovimiento("5");
        lista_input.clear();
        lista_input.push_back("5");
        agregarInput(lista_input,"5");
        for(int i=0;i<4;i++)
            agregarFrame("5",3);
        wizardAgregarImagenes(this,carpeta+"/stand/idle/",4,"5",grafico);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("5",0,hb_azul,"azules",false);
        agregarModificador("5",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("5",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("5",0,condicion);


        agregarMovimiento("6");
        agregarInput("6","6");
        for(int i=0;i<5;i++)
            agregarFrame("6",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("6",0,hb_azul,"azules",false);
        agregarModificador("6",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("6",0,condicion);
        for(int i=0;i<5;i++)
            agregarModificador("6",i,10,"posicion_x",true,false);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"6",grafico);

        agregarMovimiento("defensa");
        agregarInput("4","defensa");
        for(int i=0;i<1;i++)
            agregarFrame("defensa",3);
        hb_roja.clear();
        hb_azul.clear();
        agregarModificador("defensa",0,hb_azul,"azules",false);
        agregarModificador("defensa",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","a",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","b",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","c",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","d",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","e",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","f",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","hadouken",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","shoryuken",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","tatsumaki",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("defensa",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/block/",1,"defensa",grafico);

        agregarMovimiento("defensa");
        agregarInput("6","defensa");
        for(int i=0;i<1;i++)
            agregarFrame("defensa",3);
        hb_roja.clear();
        hb_azul.clear();
        agregarModificador("defensa",0,hb_azul,"azules",false);
        agregarModificador("defensa",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","a",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","b",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","c",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","d",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","e",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","f",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","hadouken",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","shoryuken",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","tatsumaki",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("defensa",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/block/",1,"defensa",grafico);

        agregarMovimiento("4");
        agregarInput("4","4");
        for(int i=0;i<5;i++)
            agregarFrame("4",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("4",0,hb_azul,"azules",false);
        agregarModificador("4",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("4",0,condicion);
        for(int i=0;i<5;i++)
            agregarModificador("4",i,-10,"posicion_x",true,false);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"4",grafico);

        agregarMovimiento("8");
        agregarInput("8","8");
        for(int i=0;i<12;i++)
            agregarFrame("8",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("8",0,hb_azul,"azules",false);
        agregarModificador("8",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("8",0,condicion);
        agregarModificador("8",0,"saltando","estado_posicion",false);
        wizardAgregarImagenes(this,carpeta+"/jump/8/",7,"8",grafico);

        agregarMovimiento("9");
        agregarInput("9","9");
        for(int i=0;i<7;i++)
            agregarFrame("9",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,80));
        agregarModificador("9",0,hb_azul,"azules",false);
        agregarModificador("9",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("9",0,condicion);
        agregarModificador("9",0,"saltando adelante","estado_posicion",false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"9",grafico);

        agregarMovimiento("7");
        agregarInput("7","7");
        for(int i=0;i<7;i++)
            agregarFrame("7",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,80));
        agregarModificador("7",0,hb_azul,"azules",false);
        agregarModificador("7",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("7",0,condicion);
        agregarModificador("7",0,"saltando atras","estado_posicion",false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"7",grafico);

        agregarMovimiento("defensa abajo");
        agregarInput("1","defensa abajo");
        for(int i=0;i<1;i++)
            agregarFrame("defensa abajo",3);
        hb_roja.clear();
        hb_azul.clear();
        agregarModificador("defensa abajo",0,hb_azul,"azules",false);
        agregarModificador("defensa abajo",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","a",true));
        agregarCondicion("defensa abajo",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","defensa abajo",false));
        agregarCondicion("defensa abajo",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/block/",1,"defensa abajo",grafico);

        agregarMovimiento("2");
        agregarInput("2","2");
        agregarInput("1","2");
        agregarInput("3","2");
        for(int i=0;i<1;i++)
            agregarFrame("2",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2",0,hb_azul,"azules",false);
        agregarModificador("2",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("2",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/idle/",1,"2",grafico);

        agregarMovimiento("8a");
        agregarInput("a","8a");
        agregarInput("2a","8a");
        agregarInput("4a","8a");
        agregarInput("6a","8a");
        agregarInput("8a","8a");
        agregarInput("1a","8a");
        agregarInput("3a","8a");
        agregarInput("7a","8a");
        agregarInput("9a","8a");
        agregarInput("b","8a");
        agregarInput("2b","8a");
        agregarInput("4b","8a");
        agregarInput("6b","8a");
        agregarInput("8b","8a");
        agregarInput("1b","8a");
        agregarInput("3b","8a");
        agregarInput("7b","8a");
        agregarInput("9b","8a");
        agregarInput("c","8a");
        agregarInput("2c","8a");
        agregarInput("4c","8a");
        agregarInput("6c","8a");
        agregarInput("8c","8a");
        agregarInput("1c","8a");
        agregarInput("3c","8a");
        agregarInput("7c","8a");
        agregarInput("9c","8a");
        for(int i=0;i<3;i++)
            agregarFrame("8a",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,150));
        hb_roja.push_back(HitBox(0,0,100,70));
        agregarModificador("8a",0,hb_azul,"azules",false);
        agregarModificador("8a",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","8",false));
        agregarCondicion("8a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/8a 8b 8c/",3,"8a",grafico);

        agregarMovimiento("8d");
        agregarInput("d","8d");
        agregarInput("2d","8d");
        agregarInput("4d","8d");
        agregarInput("6d","8d");
        agregarInput("8d","8d");
        agregarInput("1d","8d");
        agregarInput("3d","8d");
        agregarInput("7d","8d");
        agregarInput("9d","8d");
        agregarInput("e","8d");
        agregarInput("2e","8d");
        agregarInput("4e","8d");
        agregarInput("6e","8d");
        agregarInput("8e","8d");
        agregarInput("1e","8d");
        agregarInput("3e","8d");
        agregarInput("7e","8d");
        agregarInput("9e","8d");
        for(int i=0;i<2;i++)
            agregarFrame("8d",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,150));
        hb_roja.push_back(HitBox(0,-50,80,50));
        agregarModificador("8d",0,hb_azul,"azules",false);
        agregarModificador("8d",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","8",false));
        agregarCondicion("8d",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/8d 8e/",2,"8d",grafico);


        agregarMovimiento("8f");
        agregarInput("f","8f");
        agregarInput("2f","8f");
        agregarInput("4f","8f");
        agregarInput("6f","8f");
        agregarInput("8f","8f");
        agregarInput("1f","8f");
        agregarInput("3f","8f");
        agregarInput("7f","8f");
        agregarInput("9f","8f");
        for(int i=0;i<3;i++)
            agregarFrame("8f",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,150));
        hb_roja.push_back(HitBox(0,-20,110,50));
        agregarModificador("8f",0,hb_azul,"azules",false);
        agregarModificador("8f",0,hb_roja,"rojas",false);
        condicion.push_back(Condicion("movimiento_actual","=","8",false));
        agregarCondicion("8f",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/8f/",3,"8f",grafico);

        agregarMovimiento("9a");
        agregarInput("a","9a");
        agregarInput("2a","9a");
        agregarInput("4a","9a");
        agregarInput("6a","9a");
        agregarInput("8a","9a");
        agregarInput("1a","9a");
        agregarInput("3a","9a");
        agregarInput("7a","9a");
        agregarInput("9a","9a");
        agregarInput("b","9a");
        agregarInput("2b","9a");
        agregarInput("4b","9a");
        agregarInput("6b","9a");
        agregarInput("8b","9a");
        agregarInput("1b","9a");
        agregarInput("3b","9a");
        agregarInput("7b","9a");
        agregarInput("9b","9a");
        agregarInput("c","9a");
        agregarInput("2c","9a");
        agregarInput("4c","9a");
        agregarInput("6c","9a");
        agregarInput("8c","9a");
        agregarInput("1c","9a");
        agregarInput("3c","9a");
        agregarInput("7c","9a");
        agregarInput("9c","9a");
        for(int i=0;i<2;i++)
            agregarFrame("9a",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,140));
        hb_roja.push_back(HitBox(0,-20,80,120));
        agregarModificador("9a",0,hb_azul,"azules",false);
        agregarModificador("9a",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","9",false));
        agregarCondicion("9a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","7",false));
        agregarCondicion("9a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/9a/",2,"9a",grafico);

        agregarMovimiento("9e");
        agregarInput("d","9e");
        agregarInput("2d","9e");
        agregarInput("4d","9e");
        agregarInput("6d","9e");
        agregarInput("8d","9e");
        agregarInput("1d","9e");
        agregarInput("3d","9e");
        agregarInput("7d","9e");
        agregarInput("9d","9e");
        agregarInput("e","9e");
        agregarInput("2e","9e");
        agregarInput("4e","9e");
        agregarInput("6e","9e");
        agregarInput("8e","9e");
        agregarInput("1e","9e");
        agregarInput("3e","9e");
        agregarInput("7e","9e");
        agregarInput("9e","9e");
        agregarInput("f","9e");
        agregarInput("2f","9e");
        agregarInput("4f","9e");
        agregarInput("6f","9e");
        agregarInput("8f","9e");
        agregarInput("1f","9e");
        agregarInput("3f","9e");
        agregarInput("7f","9e");
        agregarInput("9f","9e");
        for(int i=0;i<2;i++)
            agregarFrame("9e",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,140));
        hb_roja.push_back(HitBox(0,40,130,130));
        agregarModificador("9e",0,hb_azul,"azules",false);
        agregarModificador("9e",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","9",false));
        agregarCondicion("9e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","7",false));
        agregarCondicion("9e",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/9e 9f/",2,"9e",grafico);

        agregarMovimiento("a");
        agregarInput("a","a");
        agregarInput("5a","a");
        agregarInput("4a","a");
        agregarInput("6a","a");
        for(int i=0;i<3;i++)
            agregarFrame("a",3);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        hb_roja.push_back(HitBox(0,-15,100,40));
        agregarModificador("a",0,hb_azul,"azules",false);
        agregarModificador("a",0,hb_roja,"rojas",false);
        agregarModificador("a",0,"si","atacando",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/a/",3,"a",grafico);

        agregarMovimiento("2a");
        agregarInput("2a","2a");
        agregarInput("1a","2a");
        agregarInput("3a","2a");
        for(int i=0;i<3;i++)
            agregarFrame("2a",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(20,50,110,100));
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2a",0,hb_azul,"azules",false);
        agregarModificador("2a",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("2a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("2a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/a/",3,"2a",grafico);

        agregarMovimiento("b");
        agregarInput("b","b");
        agregarInput("4b","b");
        agregarInput("6b","b");
        for(int i=0;i<5;i++)
            agregarFrame("b",3);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        hb_roja.push_back(HitBox(0,-15,140,40));
        agregarModificador("b",0,hb_azul,"azules",false);
        agregarModificador("b",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("b",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/b c/",5,"b",grafico);

        agregarMovimiento("2b");
        agregarInput("2b","2b");
        agregarInput("1b","2b");
        agregarInput("3b","2b");
        for(int i=0;i<4;i++)
            agregarFrame("2b",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(20,50,120,100));
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2b",0,hb_azul,"azules",false);
        agregarModificador("2b",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("2b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("2b",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/b/",4,"2b",grafico);

        agregarMovimiento("c");
        agregarInput("c","c");
        agregarInput("4c","c");
        agregarInput("6c","c");
        for(int i=0;i<5;i++)
            agregarFrame("c",3);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        hb_roja.push_back(HitBox(0,-15,140,40));
        agregarModificador("c",0,hb_azul,"azules",false);
        agregarModificador("c",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","9",false));
        agregarCondicion("c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("c",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/b c/",5,"c",grafico);

        agregarMovimiento("2c");
        agregarInput("2c","2c");
        agregarInput("1c","2c");
        agregarInput("3c","2c");
        for(int i=0;i<5;i++)
            agregarFrame("2c",3);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        hb_roja.push_back(HitBox(20,-100,80,100));
        agregarModificador("2c",0,hb_azul,"azules",false);
        agregarModificador("2c",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("2c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("2c",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/c/",5,"2c",grafico);

        agregarMovimiento("d");
        agregarInput("d","d");
        agregarInput("4d","d");
        agregarInput("6d","d");
        for(int i=0;i<3;i++)
            agregarFrame("d",3);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        hb_roja.push_back(HitBox(0,-50,80,40));
        agregarModificador("d",0,hb_azul,"azules",false);
        agregarModificador("d",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("d",0,condicion);
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("d",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("d",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/d e/",3,"d",grafico);

        agregarMovimiento("2d");
        agregarInput("2d","2d");
        agregarInput("1d","2d");
        agregarInput("3d","2d");
        for(int i=0;i<3;i++)
            agregarFrame("2d",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(20,140,140,190));
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2d",0,hb_azul,"azules",false);
        agregarModificador("2d",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("2d",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("2d",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/d/",3,"2d",grafico);

        agregarMovimiento("e");
        agregarInput("e","e");
        agregarInput("4e","e");
        agregarInput("6e","e");
        for(int i=0;i<3;i++)
            agregarFrame("e",3);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        hb_roja.push_back(HitBox(0,-50,80,40));
        agregarModificador("e",0,hb_azul,"azules",false);
        agregarModificador("e",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("e",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/d e/",3,"e",grafico);

        agregarMovimiento("2e");
        agregarInput("2e","2e");
        agregarInput("1e","2e");
        agregarInput("3e","2e");
        for(int i=0;i<3;i++)
            agregarFrame("2e",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(20,140,160,190));
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2e",0,hb_azul,"azules",false);
        agregarModificador("2e",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("2e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("2e",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/e/",3,"2e",grafico);

        agregarMovimiento("f");
        agregarInput("f","f");
        agregarInput("4f","f");
        agregarInput("6f","f");
        for(int i=0;i<5;i++)
            agregarFrame("f",3);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        hb_roja.push_back(HitBox(0,-50,130,40));
        agregarModificador("f",0,hb_azul,"azules",false);
        agregarModificador("f",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("f",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/f/",5,"f",grafico);

        agregarMovimiento("2f");
        agregarInput("2f","2f");
        agregarInput("1f","2f");
        agregarInput("3f","2f");
        for(int i=0;i<5;i++)
            agregarFrame("2f",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(20,140,160,190));
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2f",0,hb_azul,"azules",false);
        agregarModificador("2f",0,hb_roja,"rojas",false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        agregarCondicion("2f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        agregarCondicion("2f",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/f/",5,"2f",grafico);

        agregarMovimiento("saltando");
        agregarInput("*","saltando");
        for(int i=0;i<12;i++)
            agregarFrame("saltando",3);
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando",0,condicion);
        agregarModificador("saltando",0,"saltando","saltando_lock",false);
        agregarModificador("saltando",0,-25,"posicion_y",true,false);
        agregarModificador("saltando",1,-25,"posicion_y",true,false);
        agregarModificador("saltando",2,-25,"posicion_y",true,false);
        agregarModificador("saltando",3,-25,"posicion_y",true,false);
        agregarModificador("saltando",4,-15,"posicion_y",true,false);
        agregarModificador("saltando",5,-15,"posicion_y",true,false);
        agregarModificador("saltando",6,15,"posicion_y",true,false);
        agregarModificador("saltando",7,15,"posicion_y",true,false);
        agregarModificador("saltando",8,25,"posicion_y",true,false);
        agregarModificador("saltando",9,25,"posicion_y",true,false);
        agregarModificador("saltando",10,25,"posicion_y",true,false);
        agregarModificador("saltando",11,25,"posicion_y",true,false);
        agregarModificador("saltando",11,"","saltando_lock",false);
        agregarModificador("saltando",11,"","estado_posicion",false);

        agregarMovimiento("saltando adelante");
        agregarInput("*","saltando adelante");
        for(int i=0;i<12;i++)
            agregarFrame("saltando adelante",3);
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando adelante",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando adelante",0,condicion);
        agregarModificador("saltando adelante",0,"saltando","saltando_lock",false);
        agregarModificador("saltando adelante",0,-25,"posicion_y",true,false);
        agregarModificador("saltando adelante",1,-25,"posicion_y",true,false);
        agregarModificador("saltando adelante",2,-25,"posicion_y",true,false);
        agregarModificador("saltando adelante",3,-25,"posicion_y",true,false);
        agregarModificador("saltando adelante",4,-15,"posicion_y",true,false);
        agregarModificador("saltando adelante",5,-15,"posicion_y",true,false);
        agregarModificador("saltando adelante",6,15,"posicion_y",true,false);
        agregarModificador("saltando adelante",7,15,"posicion_y",true,false);
        agregarModificador("saltando adelante",8,25,"posicion_y",true,false);
        agregarModificador("saltando adelante",9,25,"posicion_y",true,false);
        agregarModificador("saltando adelante",10,25,"posicion_y",true,false);
        agregarModificador("saltando adelante",11,25,"posicion_y",true,false);
        agregarModificador("saltando adelante",11,"","saltando_lock",false);
        agregarModificador("saltando adelante",11,"","estado_posicion",false);
        for(int i=0;i<12;i++)
            agregarModificador("saltando adelante",i,10,"posicion_x",true,false);

        agregarMovimiento("saltando atras");
        agregarInput("*","saltando atras");
        for(int i=0;i<12;i++)
            agregarFrame("saltando atras",3);
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando atras",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando atras",0,condicion);
        agregarModificador("saltando atras",0,"saltando","saltando_lock",false);
        agregarModificador("saltando atras",0,-25,"posicion_y",true,false);
        agregarModificador("saltando atras",1,-25,"posicion_y",true,false);
        agregarModificador("saltando atras",2,-25,"posicion_y",true,false);
        agregarModificador("saltando atras",3,-25,"posicion_y",true,false);
        agregarModificador("saltando atras",4,-15,"posicion_y",true,false);
        agregarModificador("saltando atras",5,-15,"posicion_y",true,false);
        agregarModificador("saltando atras",6,15,"posicion_y",true,false);
        agregarModificador("saltando atras",7,15,"posicion_y",true,false);
        agregarModificador("saltando atras",8,25,"posicion_y",true,false);
        agregarModificador("saltando atras",9,25,"posicion_y",true,false);
        agregarModificador("saltando atras",10,25,"posicion_y",true,false);
        agregarModificador("saltando atras",11,25,"posicion_y",true,false);
        agregarModificador("saltando atras",11,"","saltando_lock",false);
        agregarModificador("saltando atras",11,"","estado_posicion",false);
        for(int i=0;i<12;i++)
            agregarModificador("saltando atras",i,-10,"posicion_x",true,false);

        agregarMovimiento("recibir");
        agregarInput("*","recibir");
        for(int i=0;i<4;i++)
            agregarFrame("recibir",3);
        condicion.clear();
        condicion.push_back(Condicion("colision_hitboxes","=","si",false));
        condicion.push_back(Condicion("recibir_lock","!=","activo",false));
        agregarCondicion("recibir",0,condicion);
        agregarModificador("recibir",0,"activo","recibir_lock",false);
        agregarModificador("recibir",0,-10,"hp_valor_actual",true,false);
        agregarModificador("recibir",3,"","recibir_lock",false);
//        agregarModificador("a",0,"si","atacando",false);
        wizardAgregarImagenes(this,carpeta+"/stand/hit/",4,"recibir",grafico);
    }
};

int main()
{
    Receiver* receiver=new Receiver();
    Parser parser;
    if(!parser.parseInput(receiver))
        cout<<"Archivo de input incorrecto";
    Input *inputa=parser.inputs[0];
    Input *inputb=parser.inputs[1];
    Grafico *grafico=new Grafico(receiver);
    Sonido *sonido = new Sonido();
    Stage *stage=new Stage(grafico->getTexture("resources/Stages/Stage02.png"),grafico->getTexture("resources/Stages/Barra_Vida.png"),grafico);
    Personaje *pa=(Personaje*)new Ryu(Barra("hp_valor_maximo","hp_valor_actual","hp_modificador_periodico","hp_periodo",video::SColor(255,255,0,0),core::rect<s32>(0,0,200,50),NULL),300,350,2,"d",grafico,NULL,inputa);
    Personaje *pb=(Personaje*)new Ryu(Barra("hp_valor_maximo","hp_valor_actual","hp_modificador_periodico","hp_periodo",video::SColor(255,255,0,0),core::rect<s32>(250,0,450,50),NULL),624,350,3,"i",grafico,NULL,inputb);

    //Menu m(stage,pa,pb,sonido,grafico,receiver);
    //m.loopMenu();

    Fighter fighter(stage,pa,pb,grafico,sonido);
    return 0;
}
