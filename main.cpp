#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "include/Input.h"
#include "include/Fighter.h"

#include"include/Parser.h"

#include "include/TinyXml/tinyxml.h"
#include <iostream>
using namespace std;
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
        personaje->agregarModificador(movimiento,i,"imagen_personaje",Imagen(grafico->getTexture(irr::io::path(str)),3,0,0),false);
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
        setString("colision_hitboxes_azules","");
        setString("colision_hadouken","");
        setString("atacando","");

        setEntero("hp_valor_maximo",250);
        setEntero("hp_valor_actual",250);
        setEntero("hp_modificador_periodico",-1);
        setEntero("hp_periodo",1);
        setEntero("daño fisico",0);

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
            agregarModificador("tatsumaki",i,"posicion_x",20,true,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,120));
        agregarModificador("tatsumaki",0,"azules",hb_azul,false);
        agregarModificador("tatsumaki",0,"rojas",hb_roja,false);
        agregarModificador("tatsumaki",3,"azules",hb_azul,false);
        agregarModificador("tatsumaki",3,"rojas",hb_roja,false);
        agregarModificador("tatsumaki",5,"azules",hb_azul,false);
        agregarModificador("tatsumaki",5,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(10,-40,125,20));
        hb_azul.push_back(HitBox(10,-20,125,30));
        hb_azul.push_back(HitBox(-50,-100,50,120));
        agregarModificador("tatsumaki",2,"rojas",hb_roja,false);
        agregarModificador("tatsumaki",2,"azules",hb_azul,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(-125,-40,-10,20));
        hb_azul.push_back(HitBox(-125,-20,-10,30));
        hb_azul.push_back(HitBox(-50,-100,50,120));
        agregarModificador("tatsumaki",4,"rojas",hb_roja,false);
        agregarModificador("tatsumaki",4,"azules",hb_azul,false);
        wizardAgregarImagenes(this,carpeta+"/special/tatsumaki/",8,"tatsumaki",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);

        agregarMovimiento("tatsumakii");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("6");
        lista_input.push_back("6d");
        agregarInput(lista_input,"tatsumakii");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("6");
        lista_input.push_back("6e");
        agregarInput(lista_input,"tatsumakii");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("6");
        lista_input.push_back("6f");
        agregarInput(lista_input,"tatsumakii");
        for(int i=0;i<8;i++)
            agregarFrame("tatsumakii",3);
        for(int i=0;i<8;i++)
            agregarModificador("tatsumakii",i,"posicion_x",-20,true,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,120));
        agregarModificador("tatsumakii",0,"azules",hb_azul,false);
        agregarModificador("tatsumakii",0,"rojas",hb_roja,false);
        agregarModificador("tatsumakii",3,"azules",hb_azul,false);
        agregarModificador("tatsumakii",3,"rojas",hb_roja,false);
        agregarModificador("tatsumakii",5,"azules",hb_azul,false);
        agregarModificador("tatsumakii",5,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(10,-40,125,20));
        hb_azul.push_back(HitBox(10,-20,125,30));
        hb_azul.push_back(HitBox(-50,-100,50,120));
        agregarModificador("tatsumakii",2,"rojas",hb_roja,false);
        agregarModificador("tatsumakii",2,"azules",hb_azul,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_roja.push_back(HitBox(-125,-40,-10,20));
        hb_azul.push_back(HitBox(-125,-20,-10,30));
        hb_azul.push_back(HitBox(-50,-100,50,120));
        agregarModificador("tatsumakii",4,"rojas",hb_roja,false);
        agregarModificador("tatsumakii",4,"azules",hb_azul,false);
        wizardAgregarImagenes(this,carpeta+"/special/tatsumaki/",8,"tatsumakii",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);

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
        for(int i=0;i<6;i++)
            agregarFrame("shoryuken",3);
        hb_roja.clear();
        hb_azul.clear();
        agregarModificador("shoryuken",0,"azules",hb_azul,false);
        agregarModificador("shoryuken",0,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(-20,-130,70,70));
        agregarModificador("shoryuken",2,"azules",hb_azul,false);
        agregarModificador("shoryuken",2,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,150));
        agregarModificador("shoryuken",3,"azules",hb_azul,false);
        agregarModificador("shoryuken",3,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,170));
        agregarModificador("shoryuken",5,"azules",hb_azul,false);
        agregarModificador("shoryuken",5,"rojas",hb_roja,false);
        wizardAgregarImagenes(this,carpeta+"/special/shoryuken/",6,"shoryuken",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);

        agregarMovimiento("shoryukeni");
        lista_input.clear();
        lista_input.push_back("4");
        lista_input.push_back("2");
        lista_input.push_back("1a");
        agregarInput(lista_input,"shoryukeni");
        lista_input.clear();
        lista_input.push_back("4");
        lista_input.push_back("2");
        lista_input.push_back("1b");
        agregarInput(lista_input,"shoryukeni");
        lista_input.clear();
        lista_input.push_back("4");
        lista_input.push_back("2");
        lista_input.push_back("1c");
        agregarInput(lista_input,"shoryukeni");
        for(int i=0;i<6;i++)
            agregarFrame("shoryukeni",3);
        hb_roja.clear();
        hb_azul.clear();
        agregarModificador("shoryukeni",0,"azules",hb_azul,false);
        agregarModificador("shoryukeni",0,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(-20,-130,70,70));
        agregarModificador("shoryukeni",2,"azules",hb_azul,false);
        agregarModificador("shoryukeni",2,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,150));
        agregarModificador("shoryukeni",3,"azules",hb_azul,false);
        agregarModificador("shoryukeni",3,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,170));
        agregarModificador("shoryukeni",5,"azules",hb_azul,false);
        agregarModificador("shoryukeni",5,"rojas",hb_roja,false);
        wizardAgregarImagenes(this,carpeta+"/special/shoryuken/",6,"shoryukeni",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);

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
        agregarModificador("hadouken",3,"iniciar hadouken","activo",false);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("hadouken",0,"azules",hb_azul,false);
        agregarModificador("hadouken",0,"rojas",hb_roja,false);
        hb_azul.push_back(HitBox(0,0,120,80));
        agregarModificador("hadouken",3,"azules",hb_azul,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);

        agregarMovimiento("hadoukeni");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("4");
        lista_input.push_back("4a");
        agregarInput(lista_input,"hadoukeni");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("4");
        lista_input.push_back("4b");
        agregarInput(lista_input,"hadoukeni");
        lista_input.clear();
        lista_input.push_back("2");
        lista_input.push_back("4");
        lista_input.push_back("4c");
        agregarInput(lista_input,"hadoukeni");
        for(int i=0;i<5;i++)
            agregarFrame("hadoukeni",3);
        wizardAgregarImagenes(this,carpeta+"/special/hadouken/",5,"hadoukeni",grafico);
        agregarModificador("hadoukeni",3,"iniciar hadoukeni","activo",false);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("hadoukeni",0,"azules",hb_azul,false);
        agregarModificador("hadoukeni",0,"rojas",hb_roja,false);
        hb_azul.push_back(HitBox(0,0,120,80));
        agregarModificador("hadoukeni",3,"azules",hb_azul,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);

        agregarMovimiento("9");
        agregarInput("9","9");
        for(int i=0;i<7;i++)
            agregarFrame("9",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,80));
        agregarModificador("9",0,"azules",hb_azul,false);
        agregarModificador("9",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("9",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("9",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("9",0,condicion);
        agregarModificador("9",0,"estado_posicion","saltando adelante",false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"9",grafico);

        agregarMovimiento("7");
        agregarInput("7","7");
        for(int i=0;i<7;i++)
            agregarFrame("7",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,80));
        agregarModificador("7",0,"azules",hb_azul,false);
        agregarModificador("7",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("7",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("7",0,condicion);
                condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("7",0,condicion);
        agregarModificador("7",0,"estado_posicion","saltando atras",false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"7",grafico);

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
        agregarModificador("5",0,"azules",hb_azul,false);
        agregarModificador("5",0,"rojas",hb_roja,false);
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
        agregarModificador("6",0,"azules",hb_azul,false);
        agregarModificador("6",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("6",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"6",grafico);

        agregarMovimiento("defensa");
        agregarInput("4","defensa");
        for(int i=0;i<1;i++)
            agregarFrame("defensa",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("defensa",0,"azules",hb_azul,false);
        agregarModificador("defensa",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensa",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/block/",1,"defensa",grafico);

        agregarMovimiento("defensai");
        agregarInput("6","defensai");
        for(int i=0;i<1;i++)
            agregarFrame("defensai",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("defensai",0,"azules",hb_azul,false);
        agregarModificador("defensai",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensai",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/block/",1,"defensai",grafico);

        agregarMovimiento("4");
        agregarInput("4","4");
        for(int i=0;i<5;i++)
            agregarFrame("4",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("4",0,"azules",hb_azul,false);
        agregarModificador("4",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("4",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"4",grafico);

        agregarMovimiento("8");
        agregarInput("8","8");
        for(int i=0;i<12;i++)
            agregarFrame("8",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("8",0,"azules",hb_azul,false);
        agregarModificador("8",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("8",0,condicion);
        agregarModificador("8",0,"estado_posicion","saltando",false);
        wizardAgregarImagenes(this,carpeta+"/jump/8/",7,"8",grafico);

        agregarMovimiento("defensa abajo");
        agregarInput("1","defensa abajo");
        for(int i=0;i<1;i++)
            agregarFrame("defensa abajo",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("defensa abajo",0,"azules",hb_azul,false);
        agregarModificador("defensa abajo",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensa abajo",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/block/",1,"defensa abajo",grafico);

        agregarMovimiento("defensa abajoi");
        agregarInput("3","defensa abajoi");
        for(int i=0;i<1;i++)
            agregarFrame("defensa abajoi",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("defensa abajoi",0,"azules",hb_azul,false);
        agregarModificador("defensa abajoi",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensa abajoi",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/block/",1,"defensa abajoi",grafico);

        agregarMovimiento("2");
        agregarInput("2","2");
        agregarInput("1","2");
        agregarInput("3","2");
        for(int i=0;i<1;i++)
            agregarFrame("2",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2",0,"azules",hb_azul,false);
        agregarModificador("2",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("8a",0,"azules",hb_azul,false);
        agregarModificador("8a",0,"rojas",hb_roja,false);
        agregarModificador("8a",2,"azules",hb_azul,false);
        agregarModificador("8a",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,0,100,70));
        hb_azul.push_back(HitBox(0,0,100,70));
        agregarModificador("8a",1,"azules",hb_azul,false);
        agregarModificador("8a",1,"rojas",hb_roja,false);
        agregarModificador("8a",0,"atacando","activo",false);
        agregarModificador("8a",2,"atacando","",false);
        agregarModificador("8a",0,"daño fisico",-10,false,true);
        agregarModificador("8a",2,"daño fisico",0,false,true);
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
        agregarModificador("8d",1,"azules",hb_azul,false);
        agregarModificador("8d",1,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,80,50));
        hb_azul.push_back(HitBox(0,-50,80,50));
        agregarModificador("8d",0,"azules",hb_azul,false);
        agregarModificador("8d",0,"rojas",hb_roja,false);
        agregarModificador("8d",0,"atacando","activo",false);
        agregarModificador("8d",1,"atacando","",false);
        agregarModificador("8d",0,"daño fisico",-10,false,true);
        agregarModificador("8d",1,"daño fisico",0,false,true);
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
        agregarModificador("8f",0,"azules",hb_azul,false);
        agregarModificador("8f",0,"rojas",hb_roja,false);
        agregarModificador("8f",2,"azules",hb_azul,false);
        agregarModificador("8f",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-20,110,50));
        hb_azul.push_back(HitBox(0,-20,110,50));
        agregarModificador("8f",1,"azules",hb_azul,false);
        agregarModificador("8f",1,"rojas",hb_roja,false);
        agregarModificador("8f",0,"atacando","activo",false);
        agregarModificador("8f",2,"atacando","",false);
        agregarModificador("8f",0,"daño fisico",-10,false,true);
        agregarModificador("8f",2,"daño fisico",0,false,true);
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
        agregarModificador("9a",0,"azules",hb_azul,false);
        agregarModificador("9a",0,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-20,80,120));
        hb_azul.push_back(HitBox(0,-20,80,120));
        agregarModificador("9a",1,"azules",hb_azul,false);
        agregarModificador("9a",1,"rojas",hb_roja,false);
        agregarModificador("9a",0,"atacando","activo",false);
        agregarModificador("9a",1,"atacando","",false);
        agregarModificador("9a",0,"daño fisico",-10,false,true);
        agregarModificador("9a",1,"daño fisico",0,false,true);
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
        for(int i=0;i<3;i++)
            agregarFrame("9e",3);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,140));
        agregarModificador("9e",0,"azules",hb_azul,false);
        agregarModificador("9e",0,"rojas",hb_roja,false);
        agregarModificador("9e",2,"azules",hb_azul,false);
        agregarModificador("9e",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,40,130,130));
        hb_azul.push_back(HitBox(0,40,130,130));
        agregarModificador("9e",1,"azules",hb_azul,false);
        agregarModificador("9e",1,"rojas",hb_roja,false);
        agregarModificador("9e",0,"atacando","activo",false);
        agregarModificador("9e",2,"atacando","",false);
        agregarModificador("9e",0,"daño fisico",-10,false,true);
        agregarModificador("9e",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","9",false));
        agregarCondicion("9e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","7",false));
        agregarCondicion("9e",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/9e 9f/",3,"9e",grafico);

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
        agregarModificador("a",0,"azules",hb_azul,false);
        agregarModificador("a",0,"rojas",hb_roja,false);
        agregarModificador("a",2,"azules",hb_azul,false);
        agregarModificador("a",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-15,100,40));
        hb_azul.push_back(HitBox(0,-15,100,40));
        agregarModificador("a",1,"azules",hb_azul,false);
        agregarModificador("a",1,"rojas",hb_roja,false);
        agregarModificador("a",0,"atacando","activo",false);
        agregarModificador("a",2,"atacando","",false);
        agregarModificador("a",0,"daño fisico",-10,false,true);
        agregarModificador("a",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2a",0,"azules",hb_azul,false);
        agregarModificador("2a",0,"rojas",hb_roja,false);
        agregarModificador("2a",2,"azules",hb_azul,false);
        agregarModificador("2a",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,50,110,100));
        hb_azul.push_back(HitBox(20,50,110,100));
        agregarModificador("2a",1,"azules",hb_azul,false);
        agregarModificador("2a",1,"rojas",hb_roja,false);
        agregarModificador("2a",0,"atacando","activo",false);
        agregarModificador("2a",2,"atacando","",false);
        agregarModificador("2a",0,"daño fisico",-10,false,true);
        agregarModificador("2a",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("b",0,"azules",hb_azul,false);
        agregarModificador("b",0,"rojas",hb_roja,false);
        agregarModificador("b",3,"azules",hb_azul,false);
        agregarModificador("b",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-15,140,40));
        hb_azul.push_back(HitBox(0,-15,140,40));
        agregarModificador("b",2,"azules",hb_azul,false);
        agregarModificador("b",2,"rojas",hb_roja,false);
        agregarModificador("b",1,"atacando","activo",false);
        agregarModificador("b",3,"atacando","",false);
        agregarModificador("b",1,"daño fisico",-20,false,true);
        agregarModificador("b",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2b",0,"azules",hb_azul,false);
        agregarModificador("2b",0,"rojas",hb_roja,false);
        agregarModificador("2b",2,"azules",hb_azul,false);
        agregarModificador("2b",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,50,120,100));
        hb_azul.push_back(HitBox(20,50,120,100));
        agregarModificador("2b",1,"azules",hb_azul,false);
        agregarModificador("2b",1,"rojas",hb_roja,false);
        agregarModificador("2b",0,"atacando","activo",false);
        agregarModificador("2b",2,"atacando","",false);
        agregarModificador("2b",0,"daño fisico",-10,false,true);
        agregarModificador("2b",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("c",0,"azules",hb_azul,false);
        agregarModificador("c",0,"rojas",hb_roja,false);
        agregarModificador("c",3,"azules",hb_azul,false);
        agregarModificador("c",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-15,140,40));
        hb_azul.push_back(HitBox(0,-15,140,40));
        agregarModificador("c",2,"azules",hb_azul,false);
        agregarModificador("c",2,"rojas",hb_roja,false);
        agregarModificador("c",1,"atacando","activo",false);
        agregarModificador("c",3,"atacando","",false);
        agregarModificador("c",1,"daño fisico",-30,false,true);
        agregarModificador("c",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("2c",0,"azules",hb_azul,false);
        agregarModificador("2c",0,"rojas",hb_roja,false);
        agregarModificador("2c",3,"azules",hb_azul,false);
        agregarModificador("2c",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,-100,80,100));
        hb_azul.push_back(HitBox(20,-100,80,100));
        agregarModificador("2c",2,"azules",hb_azul,false);
        agregarModificador("2c",2,"rojas",hb_roja,false);
        agregarModificador("2c",1,"atacando","activo",false);
        agregarModificador("2c",3,"atacando","",false);
        agregarModificador("2c",1,"daño fisico",-10,false,true);
        agregarModificador("2c",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("d",0,"azules",hb_azul,false);
        agregarModificador("d",0,"rojas",hb_roja,false);
        agregarModificador("d",2,"azules",hb_azul,false);
        agregarModificador("d",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,80,40));
        hb_azul.push_back(HitBox(0,-50,80,40));
        agregarModificador("d",1,"azules",hb_azul,false);
        agregarModificador("d",1,"rojas",hb_roja,false);
        agregarModificador("d",0,"atacando","activo",false);
        agregarModificador("d",2,"atacando","",false);
        agregarModificador("d",0,"daño fisico",-10,false,true);
        agregarModificador("d",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("d",0,condicion);
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("d",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2d",0,"azules",hb_azul,false);
        agregarModificador("2d",0,"rojas",hb_roja,false);
        agregarModificador("2d",2,"azules",hb_azul,false);
        agregarModificador("2d",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,140,140,190));
        hb_azul.push_back(HitBox(20,140,140,190));
        agregarModificador("2d",1,"azules",hb_azul,false);
        agregarModificador("2d",1,"rojas",hb_roja,false);
        agregarModificador("2d",0,"atacando","activo",false);
        agregarModificador("2d",2,"atacando","",false);
        agregarModificador("2d",0,"daño fisico",-10,false,true);
        agregarModificador("2d",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2d",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("e",0,"azules",hb_azul,false);
        agregarModificador("e",0,"rojas",hb_roja,false);
        agregarModificador("e",2,"azules",hb_azul,false);
        agregarModificador("e",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,80,40));
        hb_azul.push_back(HitBox(0,-50,80,40));
        agregarModificador("e",1,"azules",hb_azul,false);
        agregarModificador("e",1,"rojas",hb_roja,false);
        agregarModificador("e",0,"atacando","activo",false);
        agregarModificador("e",2,"atacando","",false);
        agregarModificador("e",0,"daño fisico",-10,false,true);
        agregarModificador("e",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2e",0,"azules",hb_azul,false);
        agregarModificador("2e",0,"rojas",hb_roja,false);
        agregarModificador("2e",2,"azules",hb_azul,false);
        agregarModificador("2e",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,140,160,190));
        hb_azul.push_back(HitBox(20,140,160,190));
        agregarModificador("2e",1,"azules",hb_azul,false);
        agregarModificador("2e",1,"rojas",hb_roja,false);
        agregarModificador("2e",0,"atacando","activo",false);
        agregarModificador("2e",2,"atacando","",false);
        agregarModificador("2e",0,"daño fisico",-10,false,true);
        agregarModificador("2e",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("f",0,"azules",hb_azul,false);
        agregarModificador("f",0,"rojas",hb_roja,false);
        agregarModificador("f",3,"azules",hb_azul,false);
        agregarModificador("f",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,130,40));
        hb_azul.push_back(HitBox(0,-50,130,40));
        agregarModificador("f",2,"azules",hb_azul,false);
        agregarModificador("f",2,"rojas",hb_roja,false);
        agregarModificador("f",1,"atacando","activo",false);
        agregarModificador("f",3,"atacando","",false);
        agregarModificador("f",1,"daño fisico",-10,false,true);
        agregarModificador("f",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2f",0,"azules",hb_azul,false);
        agregarModificador("2f",0,"rojas",hb_roja,false);
        agregarModificador("2f",2,"azules",hb_azul,false);
        agregarModificador("2f",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,140,160,190));
        hb_azul.push_back(HitBox(20,140,160,190));
        agregarModificador("2f",1,"azules",hb_azul,false);
        agregarModificador("2f",1,"rojas",hb_roja,false);
        agregarModificador("2f",0,"atacando","activo",false);
        agregarModificador("2f",2,"atacando","",false);
        agregarModificador("2f",0,"daño fisico",-10,false,true);
        agregarModificador("2f",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
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
        agregarModificador("saltando",0,"saltando_lock","activo",false);
        agregarModificador("saltando",0,"posicion_y",-20,true,false);
        agregarModificador("saltando",1,"posicion_y",-20,true,false);
        agregarModificador("saltando",2,"posicion_y",-20,true,false);
        agregarModificador("saltando",3,"posicion_y",-20,true,false);
        agregarModificador("saltando",4,"posicion_y",-10,true,false);
        agregarModificador("saltando",5,"posicion_y",-10,true,false);
        agregarModificador("saltando",6,"posicion_y",10,true,false);
        agregarModificador("saltando",7,"posicion_y",10,true,false);
        agregarModificador("saltando",8,"posicion_y",20,true,false);
        agregarModificador("saltando",9,"posicion_y",20,true,false);
        agregarModificador("saltando",10,"posicion_y",20,true,false);
        agregarModificador("saltando",11,"posicion_y",20,true,false);
        agregarModificador("saltando",11,"saltando_lock","",false);
        agregarModificador("saltando",11,"estado_posicion","",false);

        agregarMovimiento("saltando adelante");
        agregarInput("*","saltando adelante");
        for(int i=0;i<12;i++)
            agregarFrame("saltando adelante",3);
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando adelante",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando adelante",0,condicion);
        agregarModificador("saltando adelante",0,"saltando_lock","activo",false);
        agregarModificador("saltando adelante",0,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",1,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",2,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",3,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",4,"posicion_y",-10,true,false);
        agregarModificador("saltando adelante",5,"posicion_y",-10,true,false);
        agregarModificador("saltando adelante",6,"posicion_y",10,true,false);
        agregarModificador("saltando adelante",7,"posicion_y",10,true,false);
        agregarModificador("saltando adelante",8,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",9,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",10,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",11,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",11,"saltando_lock","",false);
        agregarModificador("saltando adelante",11,"estado_posicion","",false);
        for(int i=0;i<12;i++)
            agregarModificador("saltando adelante",i,"posicion_x",25,true,false);

        agregarMovimiento("saltando atras");
        agregarInput("*","saltando atras");
        for(int i=0;i<12;i++)
            agregarFrame("saltando atras",3);
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando atras",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando atras",0,condicion);
        agregarModificador("saltando atras",0,"saltando_lock","activo",false);
        agregarModificador("saltando atras",0,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",1,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",2,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",3,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",4,"posicion_y",-10,true,false);
        agregarModificador("saltando atras",5,"posicion_y",-10,true,false);
        agregarModificador("saltando atras",6,"posicion_y",10,true,false);
        agregarModificador("saltando atras",7,"posicion_y",10,true,false);
        agregarModificador("saltando atras",8,"posicion_y",15,true,false);
        agregarModificador("saltando atras",9,"posicion_y",15,true,false);
        agregarModificador("saltando atras",10,"posicion_y",15,true,false);
        agregarModificador("saltando atras",11,"posicion_y",15,true,false);
        agregarModificador("saltando atras",11,"saltando_lock","",false);
        agregarModificador("saltando atras",11,"estado_posicion","",false);
        for(int i=0;i<12;i++)
            agregarModificador("saltando atras",i,"posicion_x",-25,true,false);

        agregarMovimiento("caminar derecha");
        agregarInput("*","caminar derecha");
        agregarFrame("caminar derecha",3);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","no",false));
        agregarCondicion("caminar derecha",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("caminar derecha",0,condicion);
        agregarModificador("caminar derecha",0,"posicion_x",25,true,false);

        agregarMovimiento("caminar izquierda");
        agregarInput("*","caminar izquierda");
        agregarFrame("caminar izquierda",3);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("caminar izquierda",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","no",false));
        agregarCondicion("caminar izquierda",0,condicion);
        agregarModificador("caminar izquierda",0,"posicion_x",-25,true,false);

        agregarMovimiento("empujar derecha");
        agregarInput("*","empujar derecha");
        agregarFrame("empujar derecha",3);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","si",false));
        agregarCondicion("empujar derecha",0,condicion);
        agregarModificador("empujar derecha",0,"posicion_x",10,true,false);
        agregarModificador("empujar derecha",0,"posicion_x",10,true,true);

        agregarMovimiento("empujar izquerda");
        agregarInput("*","empujar izquerda");
        agregarFrame("empujar izquerda",3);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","si",false));
        agregarCondicion("empujar izquerda",0,condicion);
        agregarModificador("empujar izquerda",0,"posicion_x",-10,true,false);
        agregarModificador("empujar izquerda",0,"posicion_x",-10,true,true);

        agregarMovimiento("recibir");
        agregarInput("*","recibir");
        for(int i=0;i<12;i++)
            agregarFrame("recibir",0);
        condicion.clear();
        condicion.push_back(Condicion("colision_hitboxes","=","si",false));
        condicion.push_back(Condicion("recibir_lock","!=","activo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensai",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajoi",false));
        agregarCondicion("recibir",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("colision_hadouken","=","si",false));
        condicion.push_back(Condicion("recibir_lock","!=","activo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensai",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajoi",false));
        agregarCondicion("recibir",0,condicion);
        agregarModificador("recibir",0,"recibir_lock","activo",false);
        agregarModificador("recibir",0,"entero","hp_valor_actual","daño fisico",true,false);
        agregarModificador("recibir",3,"recibir_lock","",false);
        agregarModificador("recibir",0,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/1.png"),3,0,0),false);
        agregarModificador("recibir",1,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/1.png"),3,0,0),false);
        agregarModificador("recibir",2,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/1.png"),3,0,0),false);
        agregarModificador("recibir",3,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/2.png"),3,0,0),false);
        agregarModificador("recibir",4,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/2.png"),3,0,0),false);
        agregarModificador("recibir",5,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/2.png"),3,0,0),false);
        agregarModificador("recibir",6,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/3.png"),3,0,0),false);
        agregarModificador("recibir",7,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/3.png"),3,0,0),false);
        agregarModificador("recibir",8,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/3.png"),3,0,0),false);
        agregarModificador("recibir",9,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/4.png"),3,0,0),false);
        agregarModificador("recibir",10,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/4.png"),3,0,0),false);
        agregarModificador("recibir",11,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/4.png"),3,0,0),false);
//        wizardAgregarImagenes(this,carpeta+"/stand/hit/",4,"recibir",grafico);

        setString("iniciar hadouken","");
        setEntero("hadouken posicion x",0);
        setEntero("hadouken posicion y",350);
        setImagen("hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/1.png"),3,0,0));
        hb_roja.clear();
        hb_roja.push_back(HitBox(-50,-50,50,50));
        setHitBoxes("hadouken hitboxes",hb_roja);
        setString("hadouken estado","");
        setString("hadouken orientacion","");
        agregarProyectil("hadouken","hadouken posicion x","hadouken posicion y","hadouken imagen","hadouken hitboxes","hadouken estado","hadouken orientacion");
        agregarMovimiento("procesar hadouken");
        agregarInput("*","procesar hadouken");
        for(int i=0;i<10;i++)
            agregarFrame("procesar hadouken",3);
        condicion.clear();
        condicion.push_back(Condicion("iniciar hadouken","=","activo",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("procesar hadouken",0,condicion);
        agregarModificador("procesar hadouken",0,"hadouken orientacion","d",false);
        agregarModificador("procesar hadouken",0,"iniciar hadouken","",false);
        agregarModificador("procesar hadouken",0,"hadouken estado","activo",false);
        agregarModificador("procesar hadouken",9,"hadouken estado","",false);
        agregarModificador("procesar hadouken",0,"daño fisico",-10,false,true);
        agregarModificador("procesar hadouken",9,"daño fisico",0,false,true);
        agregarModificador("procesar hadouken",0,"entero","hadouken posicion x","posicion_x",false,false);
        agregarModificador("procesar hadouken",0,"hadouken posicion x",125,true,false);
        for(int i=1;i<10;i++)
        {
            if(i%2==0)
                agregarModificador("procesar hadouken",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/1.png"),3,0,0),false);
            else
                agregarModificador("procesar hadouken",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/2.png"),3,0,0),false);
            agregarModificador("procesar hadouken",i,"hadouken posicion x",25,true,false);
        }

        setString("iniciar hadoukeni","");
        agregarMovimiento("procesar hadoukeni");
        agregarInput("*","procesar hadoukeni");
        for(int i=0;i<10;i++)
            agregarFrame("procesar hadoukeni",3);
        condicion.clear();
        condicion.push_back(Condicion("iniciar hadoukeni","=","activo",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("procesar hadoukeni",0,condicion);
        agregarModificador("procesar hadoukeni",0,"hadouken orientacion","i",false);
        agregarModificador("procesar hadoukeni",0,"iniciar hadoukeni","",false);
        agregarModificador("procesar hadoukeni",0,"hadouken estado","activo",false);
        agregarModificador("procesar hadoukeni",9,"hadouken estado","",false);
        agregarModificador("procesar hadoukeni",0,"daño fisico",-10,false,true);
        agregarModificador("procesar hadoukeni",9,"daño fisico",0,false,true);
        agregarModificador("procesar hadoukeni",0,"entero","hadouken posicion x","posicion_x",false,false);
        agregarModificador("procesar hadoukeni",0,"hadouken posicion x",-125,true,false);
        for(int i=1;i<10;i++)
        {
            if(i%2==0)
                agregarModificador("procesar hadoukeni",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/1.png"),3,0,0),false);
            else
                agregarModificador("procesar hadoukeni",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/2.png"),3,0,0),false);
            agregarModificador("procesar hadoukeni",i,"hadouken posicion x",-25,true,false);
        }

        agregarMovimiento("5 aereo");
        agregarInput("*","5 aereo");
        agregarFrame("5 aereo",0);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","=","activo",false));
        agregarCondicion("5 aereo",0,condicion);
        agregarModificador("5 aereo",0,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/jump/idle/1.png"),3,0,0),false);

        agregarMovimiento("separar");
        agregarInput("*","separar");
        agregarFrame("separar",0);
        condicion.clear();
        condicion.push_back(Condicion("colision_hitboxes","=","si",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("separar",0,condicion);
        agregarModificador("separar",0,"posicion_x",-10,true,false);
        agregarModificador("separar",0,"posicion_x",10,true,true);

        agregarMovimiento("separari");
        agregarInput("*","separari");
        agregarFrame("separari",0);
        condicion.clear();
        condicion.push_back(Condicion("colision_hitboxes","=","si",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("separari",0,condicion);
        agregarModificador("separari",0,"posicion_x",10,true,false);
        agregarModificador("separari",0,"posicion_x",-10,true,true);
    }
};



class RyuXml : Personaje
{
public:
    void imprimirXml(TiXmlDocument *doc)
    {
        //doc->Print( stdout );
    		//Lo imprimimos con TiXmlPrinter
            TiXmlPrinter printer;
            doc->Accept( &printer );
            fprintf( stdout, "%s", printer.CStr() );
    }

    TiXmlDocument abrirXml(char* archivo)
    {
        TiXmlDocument doc( archivo );
        doc.LoadFile();
        return doc;
    }

    const char* getValor(TiXmlDocument *doc,char* str_nodo,int posicion,char* str_atributo)
    {
        //Declaracion de variables
        TiXmlNode* node = 0;
        TiXmlElement* padre = 0;
        TiXmlElement* hijo = 0;
        //Buscamos el primer nodo que se llame "str_nodo"
        node = doc->FirstChild( str_nodo );
        assert( node );
        //Lo convertimos a elemento y lo metemos en padre
        padre = node->ToElement();
        assert( padre  );
        //Buscamos el posicionesimo item y lo metemos en node
        node = padre->FirstChildElement();
        for(int i=0;i<posicion;i++)
            node=node->NextSiblingElement();
        assert( node );
        hijo=node->ToElement();
        assert(hijo);
        return hijo->Attribute(str_atributo);
    }

    RyuXml(Barra hp,int px,int py,int a,stringw orientacion,Grafico* grafico,Personaje *personaje_contrario,Input* input)
    {
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
        setString("colision_hitboxes_azules","");
        setString("colision_hadouken","");
        setString("atacando","");

        setEntero("hp_valor_maximo",250);
        setEntero("hp_valor_actual",250);
        setEntero("hp_modificador_periodico",-1);
        setEntero("hp_periodo",1);
        setEntero("daño fisico",0);

        enteros["posicion_x"]=px;
        enteros["posicion_y"]=py;

        barras["hp"]=hp;

        vector<HitBox> hb_vacia;
        hitboxes["azules"]=hb_vacia;
        hitboxes["rojas"]=hb_vacia;

        vector<Condicion> condicion;
        vector<stringw> lista_input;

        //Desde Xml
        stringw carpeta="resources/Personajes/RyuSF2";
		//Abrir personaje.xml
		TiXmlDocument doc_t=abrirXml((char *)"resources/Personajes/RyuSF2/Ryu.xml");
        TiXmlDocument *doc;
        doc=&doc_t;
		//Lo imprimimos
		imprimirXml(doc);
		//pruebas
		//for each Movimiento
		for(TiXmlNode* nodo=doc->FirstChild("Movimiento");
                nodo!=NULL;
                nodo=nodo->NextSibling("Movimiento"))
        {
            TiXmlElement *elemento=nodo->ToElement();
            stringw nombre(elemento->Attribute("nombre"));
            agregarMovimiento(nombre);
            //For each Input
            for(TiXmlNode* nodo_input=nodo->FirstChild("Input");
                    nodo_input!=NULL;
                    nodo_input=nodo_input->NextSibling("Input"))
            {
                vector<stringw> lista_botones;
                for(TiXmlElement *elemento_boton=nodo_input->FirstChild("boton")->ToElement();
                        elemento_boton!=NULL;
                        elemento_boton=elemento_boton->NextSiblingElement("boton"))
                {
                    stringw boton(elemento_boton->Attribute("valor"));
                    lista_botones.push_back(boton);
                }
                agregarInput(lista_botones,nombre);
            }
            //For each Frame
            int frame=0;
            for(TiXmlNode* nodo_frame=nodo->FirstChild("Frame");
                    nodo_frame!=NULL;
                    nodo_frame=nodo_frame->NextSibling("Frame"))
            {
                TiXmlElement *elemento_frame=nodo_frame->ToElement();
                agregarFrame(nombre,atoi(elemento_frame->Attribute("duracion")));
                //For each Modificador
                if(!nodo_frame->NoChildren())
                {
                    for(TiXmlElement *elemento_modificador=nodo_frame->FirstChild("Modificador")->ToElement();
                            elemento_modificador!=NULL;
                            elemento_modificador=elemento_modificador->NextSiblingElement("Modificador"))
                    {
                        stringw tipo(elemento_modificador->Attribute("tipo"));
                        if(tipo=="Entero")
                        {
                            stringw str_variable(elemento_modificador->Attribute("variable"));
                            stringw str_contrario(elemento_modificador->Attribute("contrario"));
                            stringw str_relativo(elemento_modificador->Attribute("relativo"));
                            int valor=atoi(elemento_modificador->Attribute("valor"));
                            bool contrario=(str_contrario=="si");
                            bool relativo=(str_relativo=="si");
                            agregarModificador(nombre,frame,str_variable,valor,relativo,contrario);
                        }
                        if(tipo=="Hitbox")
                        {
                            vector <HitBox> hitbox;
                            stringw str_variable(elemento_modificador->Attribute("variable"));
                            stringw str_contrario(elemento_modificador->Attribute("contrario"));
                            bool contrario=(str_contrario=="si");
                            if(!elemento_modificador->NoChildren())
                            {
                                for(TiXmlElement *elemento_hitbox=elemento_modificador->FirstChild("Hitbox")->ToElement();
                                        elemento_hitbox!=NULL;
                                        elemento_hitbox=elemento_hitbox->NextSiblingElement("Hitbox"))
                                {
                                    int x1=atoi(elemento_hitbox->Attribute("x1"));
                                    int y1=atoi(elemento_hitbox->Attribute("y1"));
                                    int x2=atoi(elemento_hitbox->Attribute("x2"));
                                    int y2=atoi(elemento_hitbox->Attribute("y2"));
                                    hitbox.push_back(HitBox(x1,y1,x2,y2));
                                }
                            }
                            agregarModificador(nombre,frame,str_variable,hitbox,contrario);
                        }
                        if(tipo=="Imagen")
                        {
                            stringw str_variable(elemento_modificador->Attribute("variable"));
                            stringw path(elemento_modificador->Attribute("path"));
                            int escala=atoi(elemento_modificador->Attribute("escala"));
                            int alineacion_x=atoi(elemento_modificador->Attribute("alineacion_x"));
                            int alineacion_y=atoi(elemento_modificador->Attribute("alineacion_y"));
                            stringw str_contrario(elemento_modificador->Attribute("contrario"));
                            bool contrario=(str_contrario=="si");
                            agregarModificador(nombre,frame,str_variable,Imagen(grafico->getTexture(irr::io::path(path)),escala,alineacion_x,alineacion_y),contrario);
                        }
                    }
                }
                frame++;
            }
        }
        //especiales
        //agregarMovimiento("tatsumaki");
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("tatsumaki",0,condicion);

        //agregarMovimiento("tatsumakii");
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("tatsumakii",0,condicion);

        //agregarMovimiento("shoryuken");
        hb_roja.clear();
        hb_azul.clear();
        agregarModificador("shoryuken",0,"azules",hb_azul,false);
        agregarModificador("shoryuken",0,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(-20,-130,70,70));
        agregarModificador("shoryuken",2,"azules",hb_azul,false);
        agregarModificador("shoryuken",2,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,150));
        agregarModificador("shoryuken",3,"azules",hb_azul,false);
        agregarModificador("shoryuken",3,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,170));
        agregarModificador("shoryuken",5,"azules",hb_azul,false);
        agregarModificador("shoryuken",5,"rojas",hb_roja,false);
        wizardAgregarImagenes(this,carpeta+"/special/shoryuken/",6,"shoryuken",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("shoryuken",0,condicion);

        //agregarMovimiento("shoryukeni");
        hb_roja.clear();
        hb_azul.clear();
        agregarModificador("shoryukeni",0,"azules",hb_azul,false);
        agregarModificador("shoryukeni",0,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(-20,-130,70,70));
        agregarModificador("shoryukeni",2,"azules",hb_azul,false);
        agregarModificador("shoryukeni",2,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,150));
        agregarModificador("shoryukeni",3,"azules",hb_azul,false);
        agregarModificador("shoryukeni",3,"rojas",hb_roja,false);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-100,50,170));
        agregarModificador("shoryukeni",5,"azules",hb_azul,false);
        agregarModificador("shoryukeni",5,"rojas",hb_roja,false);
        wizardAgregarImagenes(this,carpeta+"/special/shoryuken/",6,"shoryukeni",grafico);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("shoryukeni",0,condicion);

        //agregarMovimiento("hadouken");
        wizardAgregarImagenes(this,carpeta+"/special/hadouken/",5,"hadouken",grafico);
        agregarModificador("hadouken",3,"iniciar hadouken","activo",false);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("hadouken",0,"azules",hb_azul,false);
        agregarModificador("hadouken",0,"rojas",hb_roja,false);
        hb_azul.push_back(HitBox(0,0,120,80));
        agregarModificador("hadouken",3,"azules",hb_azul,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadouken",0,condicion);

        //agregarMovimiento("hadoukeni");
        wizardAgregarImagenes(this,carpeta+"/special/hadouken/",5,"hadoukeni",grafico);
        agregarModificador("hadoukeni",3,"iniciar hadoukeni","activo",false);
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("hadoukeni",0,"azules",hb_azul,false);
        agregarModificador("hadoukeni",0,"rojas",hb_roja,false);
        hb_azul.push_back(HitBox(0,0,120,80));
        agregarModificador("hadoukeni",3,"azules",hb_azul,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("hadoukeni",0,condicion);

        //agregarMovimiento("9");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,80));
        agregarModificador("9",0,"azules",hb_azul,false);
        agregarModificador("9",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("9",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("9",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("9",0,condicion);
        agregarModificador("9",0,"estado_posicion","saltando adelante",false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"9",grafico);

        //agregarMovimiento("7");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,80));
        agregarModificador("7",0,"azules",hb_azul,false);
        agregarModificador("7",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("7",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("7",0,condicion);
                condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("7",0,condicion);
        agregarModificador("7",0,"estado_posicion","saltando atras",false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"7",grafico);

        //agregarMovimiento("5");
        wizardAgregarImagenes(this,carpeta+"/stand/idle/",4,"5",grafico);
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("5",0,"azules",hb_azul,false);
        agregarModificador("5",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        agregarCondicion("5",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        agregarCondicion("5",0,condicion);


        //agregarMovimiento("6");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("6",0,"azules",hb_azul,false);
        agregarModificador("6",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("6",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"6",grafico);

        //agregarMovimiento("defensa");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("defensa",0,"azules",hb_azul,false);
        agregarModificador("defensa",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensa",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/block/",1,"defensa",grafico);

        //agregarMovimiento("defensai");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("defensai",0,"azules",hb_azul,false);
        agregarModificador("defensai",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensai",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/block/",1,"defensai",grafico);

        //agregarMovimiento("4");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("4",0,"azules",hb_azul,false);
        agregarModificador("4",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("4",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"4",grafico);

        //agregarMovimiento("8");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("8",0,"azules",hb_azul,false);
        agregarModificador("8",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("8",0,condicion);
        agregarModificador("8",0,"estado_posicion","saltando",false);
        wizardAgregarImagenes(this,carpeta+"/jump/8/",7,"8",grafico);

        //agregarMovimiento("defensa abajo");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("defensa abajo",0,"azules",hb_azul,false);
        agregarModificador("defensa abajo",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensa abajo",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/block/",1,"defensa abajo",grafico);

        //agregarMovimiento("defensa abajoi");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("defensa abajoi",0,"azules",hb_azul,false);
        agregarModificador("defensa abajoi",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("atacando","=","activo",true));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("defensa abajoi",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/block/",1,"defensa abajoi",grafico);

        //agregarMovimiento("2");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2",0,"azules",hb_azul,false);
        agregarModificador("2",0,"rojas",hb_roja,false);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/idle/",1,"2",grafico);

        //agregarMovimiento("8a");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,150));
        agregarModificador("8a",0,"azules",hb_azul,false);
        agregarModificador("8a",0,"rojas",hb_roja,false);
        agregarModificador("8a",2,"azules",hb_azul,false);
        agregarModificador("8a",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,0,100,70));
        hb_azul.push_back(HitBox(0,0,100,70));
        agregarModificador("8a",1,"azules",hb_azul,false);
        agregarModificador("8a",1,"rojas",hb_roja,false);
        agregarModificador("8a",0,"atacando","activo",false);
        agregarModificador("8a",2,"atacando","",false);
        agregarModificador("8a",0,"daño fisico",-10,false,true);
        agregarModificador("8a",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","8",false));
        agregarCondicion("8a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/8a 8b 8c/",3,"8a",grafico);

        //agregarMovimiento("8d");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,150));
        agregarModificador("8d",1,"azules",hb_azul,false);
        agregarModificador("8d",1,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,80,50));
        hb_azul.push_back(HitBox(0,-50,80,50));
        agregarModificador("8d",0,"azules",hb_azul,false);
        agregarModificador("8d",0,"rojas",hb_roja,false);
        agregarModificador("8d",0,"atacando","activo",false);
        agregarModificador("8d",1,"atacando","",false);
        agregarModificador("8d",0,"daño fisico",-10,false,true);
        agregarModificador("8d",1,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","8",false));
        agregarCondicion("8d",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/8d 8e/",2,"8d",grafico);


        //agregarMovimiento("8f");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,-50,50,150));
        agregarModificador("8f",0,"azules",hb_azul,false);
        agregarModificador("8f",0,"rojas",hb_roja,false);
        agregarModificador("8f",2,"azules",hb_azul,false);
        agregarModificador("8f",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-20,110,50));
        hb_azul.push_back(HitBox(0,-20,110,50));
        agregarModificador("8f",1,"azules",hb_azul,false);
        agregarModificador("8f",1,"rojas",hb_roja,false);
        agregarModificador("8f",0,"atacando","activo",false);
        agregarModificador("8f",2,"atacando","",false);
        agregarModificador("8f",0,"daño fisico",-10,false,true);
        agregarModificador("8f",2,"daño fisico",0,false,true);
        condicion.push_back(Condicion("movimiento_actual","=","8",false));
        agregarCondicion("8f",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/8f/",3,"8f",grafico);

        //agregarMovimiento("9a");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,140));
        agregarModificador("9a",0,"azules",hb_azul,false);
        agregarModificador("9a",0,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-20,80,120));
        hb_azul.push_back(HitBox(0,-20,80,120));
        agregarModificador("9a",1,"azules",hb_azul,false);
        agregarModificador("9a",1,"rojas",hb_roja,false);
        agregarModificador("9a",0,"atacando","activo",false);
        agregarModificador("9a",1,"atacando","",false);
        agregarModificador("9a",0,"daño fisico",-10,false,true);
        agregarModificador("9a",1,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","9",false));
        agregarCondicion("9a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","7",false));
        agregarCondicion("9a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/9a/",2,"9a",grafico);

        //agregarMovimiento("9e");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-70,-70,80,140));
        agregarModificador("9e",0,"azules",hb_azul,false);
        agregarModificador("9e",0,"rojas",hb_roja,false);
        agregarModificador("9e",2,"azules",hb_azul,false);
        agregarModificador("9e",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,40,130,130));
        hb_azul.push_back(HitBox(0,40,130,130));
        agregarModificador("9e",1,"azules",hb_azul,false);
        agregarModificador("9e",1,"rojas",hb_roja,false);
        agregarModificador("9e",0,"atacando","activo",false);
        agregarModificador("9e",2,"atacando","",false);
        agregarModificador("9e",0,"daño fisico",-10,false,true);
        agregarModificador("9e",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","9",false));
        agregarCondicion("9e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","7",false));
        agregarCondicion("9e",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/jump/9e 9f/",3,"9e",grafico);

        //agregarMovimiento("a");
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("a",0,"azules",hb_azul,false);
        agregarModificador("a",0,"rojas",hb_roja,false);
        agregarModificador("a",2,"azules",hb_azul,false);
        agregarModificador("a",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-15,100,40));
        hb_azul.push_back(HitBox(0,-15,100,40));
        agregarModificador("a",1,"azules",hb_azul,false);
        agregarModificador("a",1,"rojas",hb_roja,false);
        agregarModificador("a",0,"atacando","activo",false);
        agregarModificador("a",2,"atacando","",false);
        agregarModificador("a",0,"daño fisico",-10,false,true);
        agregarModificador("a",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/a/",3,"a",grafico);

        //agregarMovimiento("2a");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2a",0,"azules",hb_azul,false);
        agregarModificador("2a",0,"rojas",hb_roja,false);
        agregarModificador("2a",2,"azules",hb_azul,false);
        agregarModificador("2a",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,50,110,100));
        hb_azul.push_back(HitBox(20,50,110,100));
        agregarModificador("2a",1,"azules",hb_azul,false);
        agregarModificador("2a",1,"rojas",hb_roja,false);
        agregarModificador("2a",0,"atacando","activo",false);
        agregarModificador("2a",2,"atacando","",false);
        agregarModificador("2a",0,"daño fisico",-10,false,true);
        agregarModificador("2a",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2a",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2a",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/a/",3,"2a",grafico);

        //agregarMovimiento("b");
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("b",0,"azules",hb_azul,false);
        agregarModificador("b",0,"rojas",hb_roja,false);
        agregarModificador("b",3,"azules",hb_azul,false);
        agregarModificador("b",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-15,140,40));
        hb_azul.push_back(HitBox(0,-15,140,40));
        agregarModificador("b",2,"azules",hb_azul,false);
        agregarModificador("b",2,"rojas",hb_roja,false);
        agregarModificador("b",1,"atacando","activo",false);
        agregarModificador("b",3,"atacando","",false);
        agregarModificador("b",1,"daño fisico",-20,false,true);
        agregarModificador("b",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("b",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/b c/",5,"b",grafico);

        //agregarMovimiento("2b");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2b",0,"azules",hb_azul,false);
        agregarModificador("2b",0,"rojas",hb_roja,false);
        agregarModificador("2b",2,"azules",hb_azul,false);
        agregarModificador("2b",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,50,120,100));
        hb_azul.push_back(HitBox(20,50,120,100));
        agregarModificador("2b",1,"azules",hb_azul,false);
        agregarModificador("2b",1,"rojas",hb_roja,false);
        agregarModificador("2b",0,"atacando","activo",false);
        agregarModificador("2b",2,"atacando","",false);
        agregarModificador("2b",0,"daño fisico",-10,false,true);
        agregarModificador("2b",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2b",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2b",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/b/",4,"2b",grafico);

        //agregarMovimiento("c");
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("c",0,"azules",hb_azul,false);
        agregarModificador("c",0,"rojas",hb_roja,false);
        agregarModificador("c",3,"azules",hb_azul,false);
        agregarModificador("c",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-15,140,40));
        hb_azul.push_back(HitBox(0,-15,140,40));
        agregarModificador("c",2,"azules",hb_azul,false);
        agregarModificador("c",2,"rojas",hb_roja,false);
        agregarModificador("c",1,"atacando","activo",false);
        agregarModificador("c",3,"atacando","",false);
        agregarModificador("c",1,"daño fisico",-30,false,true);
        agregarModificador("c",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("c",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/b c/",5,"c",grafico);

        //agregarMovimiento("2c");
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("2c",0,"azules",hb_azul,false);
        agregarModificador("2c",0,"rojas",hb_roja,false);
        agregarModificador("2c",3,"azules",hb_azul,false);
        agregarModificador("2c",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,-100,80,100));
        hb_azul.push_back(HitBox(20,-100,80,100));
        agregarModificador("2c",2,"azules",hb_azul,false);
        agregarModificador("2c",2,"rojas",hb_roja,false);
        agregarModificador("2c",1,"atacando","activo",false);
        agregarModificador("2c",3,"atacando","",false);
        agregarModificador("2c",1,"daño fisico",-10,false,true);
        agregarModificador("2c",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2c",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2c",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/c/",5,"2c",grafico);

        //agregarMovimiento("d");
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("d",0,"azules",hb_azul,false);
        agregarModificador("d",0,"rojas",hb_roja,false);
        agregarModificador("d",2,"azules",hb_azul,false);
        agregarModificador("d",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,80,40));
        hb_azul.push_back(HitBox(0,-50,80,40));
        agregarModificador("d",1,"azules",hb_azul,false);
        agregarModificador("d",1,"rojas",hb_roja,false);
        agregarModificador("d",0,"atacando","activo",false);
        agregarModificador("d",2,"atacando","",false);
        agregarModificador("d",0,"daño fisico",-10,false,true);
        agregarModificador("d",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("d",0,condicion);
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("d",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("d",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/d e/",3,"d",grafico);

        //agregarMovimiento("2d");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2d",0,"azules",hb_azul,false);
        agregarModificador("2d",0,"rojas",hb_roja,false);
        agregarModificador("2d",2,"azules",hb_azul,false);
        agregarModificador("2d",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,140,140,190));
        hb_azul.push_back(HitBox(20,140,140,190));
        agregarModificador("2d",1,"azules",hb_azul,false);
        agregarModificador("2d",1,"rojas",hb_roja,false);
        agregarModificador("2d",0,"atacando","activo",false);
        agregarModificador("2d",2,"atacando","",false);
        agregarModificador("2d",0,"daño fisico",-10,false,true);
        agregarModificador("2d",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2d",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2d",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/d/",3,"2d",grafico);

        //agregarMovimiento("e");
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("e",0,"azules",hb_azul,false);
        agregarModificador("e",0,"rojas",hb_roja,false);
        agregarModificador("e",2,"azules",hb_azul,false);
        agregarModificador("e",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,80,40));
        hb_azul.push_back(HitBox(0,-50,80,40));
        agregarModificador("e",1,"azules",hb_azul,false);
        agregarModificador("e",1,"rojas",hb_roja,false);
        agregarModificador("e",0,"atacando","activo",false);
        agregarModificador("e",2,"atacando","",false);
        agregarModificador("e",0,"daño fisico",-10,false,true);
        agregarModificador("e",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("e",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/d e/",3,"e",grafico);

        //agregarMovimiento("2e");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2e",0,"azules",hb_azul,false);
        agregarModificador("2e",0,"rojas",hb_roja,false);
        agregarModificador("2e",2,"azules",hb_azul,false);
        agregarModificador("2e",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,140,160,190));
        hb_azul.push_back(HitBox(20,140,160,190));
        agregarModificador("2e",1,"azules",hb_azul,false);
        agregarModificador("2e",1,"rojas",hb_roja,false);
        agregarModificador("2e",0,"atacando","activo",false);
        agregarModificador("2e",2,"atacando","",false);
        agregarModificador("2e",0,"daño fisico",-10,false,true);
        agregarModificador("2e",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2e",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2e",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/e/",3,"2e",grafico);

        //agregarMovimiento("f");
        hb_azul.clear();
        hb_roja.clear();
        hb_azul.push_back(HitBox(-50,-50,50,200));
        agregarModificador("f",0,"azules",hb_azul,false);
        agregarModificador("f",0,"rojas",hb_roja,false);
        agregarModificador("f",3,"azules",hb_azul,false);
        agregarModificador("f",3,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(0,-50,130,40));
        hb_azul.push_back(HitBox(0,-50,130,40));
        agregarModificador("f",2,"azules",hb_azul,false);
        agregarModificador("f",2,"rojas",hb_roja,false);
        agregarModificador("f",1,"atacando","activo",false);
        agregarModificador("f",3,"atacando","",false);
        agregarModificador("f",1,"daño fisico",-10,false,true);
        agregarModificador("f",3,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("f",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/stand/f/",5,"f",grafico);

        //agregarMovimiento("2f");
        hb_roja.clear();
        hb_azul.clear();
        hb_azul.push_back(HitBox(-50,50,50,200));
        agregarModificador("2f",0,"azules",hb_azul,false);
        agregarModificador("2f",0,"rojas",hb_roja,false);
        agregarModificador("2f",2,"azules",hb_azul,false);
        agregarModificador("2f",2,"rojas",hb_roja,false);
        hb_roja.push_back(HitBox(20,140,160,190));
        hb_azul.push_back(HitBox(20,140,160,190));
        agregarModificador("2f",1,"azules",hb_azul,false);
        agregarModificador("2f",1,"rojas",hb_roja,false);
        agregarModificador("2f",0,"atacando","activo",false);
        agregarModificador("2f",2,"atacando","",false);
        agregarModificador("2f",0,"daño fisico",-10,false,true);
        agregarModificador("2f",2,"daño fisico",0,false,true);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","2",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2f",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","!=","activo",false));
        agregarCondicion("2f",0,condicion);
        wizardAgregarImagenes(this,carpeta+"/crouch/f/",5,"2f",grafico);

        //agregarMovimiento("saltando");
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando",0,condicion);
        agregarModificador("saltando",0,"saltando_lock","activo",false);
        agregarModificador("saltando",0,"posicion_y",-20,true,false);
        agregarModificador("saltando",1,"posicion_y",-20,true,false);
        agregarModificador("saltando",2,"posicion_y",-20,true,false);
        agregarModificador("saltando",3,"posicion_y",-20,true,false);
        agregarModificador("saltando",4,"posicion_y",-10,true,false);
        agregarModificador("saltando",5,"posicion_y",-10,true,false);
        agregarModificador("saltando",6,"posicion_y",10,true,false);
        agregarModificador("saltando",7,"posicion_y",10,true,false);
        agregarModificador("saltando",8,"posicion_y",20,true,false);
        agregarModificador("saltando",9,"posicion_y",20,true,false);
        agregarModificador("saltando",10,"posicion_y",20,true,false);
        agregarModificador("saltando",11,"posicion_y",20,true,false);
        agregarModificador("saltando",11,"saltando_lock","",false);
        agregarModificador("saltando",11,"estado_posicion","",false);

        //agregarMovimiento("saltando adelante");
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando adelante",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando adelante",0,condicion);
        agregarModificador("saltando adelante",0,"saltando_lock","activo",false);
        agregarModificador("saltando adelante",0,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",1,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",2,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",3,"posicion_y",-20,true,false);
        agregarModificador("saltando adelante",4,"posicion_y",-10,true,false);
        agregarModificador("saltando adelante",5,"posicion_y",-10,true,false);
        agregarModificador("saltando adelante",6,"posicion_y",10,true,false);
        agregarModificador("saltando adelante",7,"posicion_y",10,true,false);
        agregarModificador("saltando adelante",8,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",9,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",10,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",11,"posicion_y",20,true,false);
        agregarModificador("saltando adelante",11,"saltando_lock","",false);
        agregarModificador("saltando adelante",11,"estado_posicion","",false);
        for(int i=0;i<12;i++)
            agregarModificador("saltando adelante",i,"posicion_x",25,true,false);

        //agregarMovimiento("saltando atras");
        condicion.clear();
        condicion.push_back(Condicion("estado_posicion","=","saltando atras",false));
        condicion.push_back(Condicion("saltando_lock","=","",false));
        agregarCondicion("saltando atras",0,condicion);
        agregarModificador("saltando atras",0,"saltando_lock","activo",false);
        agregarModificador("saltando atras",0,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",1,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",2,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",3,"posicion_y",-15,true,false);
        agregarModificador("saltando atras",4,"posicion_y",-10,true,false);
        agregarModificador("saltando atras",5,"posicion_y",-10,true,false);
        agregarModificador("saltando atras",6,"posicion_y",10,true,false);
        agregarModificador("saltando atras",7,"posicion_y",10,true,false);
        agregarModificador("saltando atras",8,"posicion_y",15,true,false);
        agregarModificador("saltando atras",9,"posicion_y",15,true,false);
        agregarModificador("saltando atras",10,"posicion_y",15,true,false);
        agregarModificador("saltando atras",11,"posicion_y",15,true,false);
        agregarModificador("saltando atras",11,"saltando_lock","",false);
        agregarModificador("saltando atras",11,"estado_posicion","",false);
        for(int i=0;i<12;i++)
            agregarModificador("saltando atras",i,"posicion_x",-25,true,false);

        //agregarMovimiento("caminar derecha");
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","no",false));
        agregarCondicion("caminar derecha",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("caminar derecha",0,condicion);
        agregarModificador("caminar derecha",0,"posicion_x",25,true,false);

        //agregarMovimiento("caminar izquierda");
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("caminar izquierda",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","no",false));
        agregarCondicion("caminar izquierda",0,condicion);
        agregarModificador("caminar izquierda",0,"posicion_x",-25,true,false);

        //agregarMovimiento("empujar derecha");
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","6",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","si",false));
        agregarCondicion("empujar derecha",0,condicion);
        agregarModificador("empujar derecha",0,"posicion_x",10,true,false);
        agregarModificador("empujar derecha",0,"posicion_x",10,true,true);

        //agregarMovimiento("empujar izquerda");
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","4",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        condicion.push_back(Condicion("colision_hitboxes_azules","=","si",false));
        agregarCondicion("empujar izquerda",0,condicion);
        agregarModificador("empujar izquerda",0,"posicion_x",-10,true,false);
        agregarModificador("empujar izquerda",0,"posicion_x",-10,true,true);

        //agregarMovimiento("recibir");
        condicion.clear();
        condicion.push_back(Condicion("colision_hitboxes","=","si",false));
        condicion.push_back(Condicion("recibir_lock","!=","activo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensai",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajoi",false));
        agregarCondicion("recibir",0,condicion);
        condicion.clear();
        condicion.push_back(Condicion("colision_hadouken","=","si",false));
        condicion.push_back(Condicion("recibir_lock","!=","activo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensai",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajo",false));
        condicion.push_back(Condicion("movimiento_actual","!=","defensa abajoi",false));
        agregarCondicion("recibir",0,condicion);
        agregarModificador("recibir",0,"recibir_lock","activo",false);
        agregarModificador("recibir",0,"entero","hp_valor_actual","daño fisico",true,false);
        agregarModificador("recibir",3,"recibir_lock","",false);
        agregarModificador("recibir",0,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/1.png"),3,0,0),false);
        agregarModificador("recibir",1,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/1.png"),3,0,0),false);
        agregarModificador("recibir",2,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/1.png"),3,0,0),false);
        agregarModificador("recibir",3,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/2.png"),3,0,0),false);
        agregarModificador("recibir",4,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/2.png"),3,0,0),false);
        agregarModificador("recibir",5,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/2.png"),3,0,0),false);
        agregarModificador("recibir",6,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/3.png"),3,0,0),false);
        agregarModificador("recibir",7,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/3.png"),3,0,0),false);
        agregarModificador("recibir",8,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/3.png"),3,0,0),false);
        agregarModificador("recibir",9,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/4.png"),3,0,0),false);
        agregarModificador("recibir",10,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/4.png"),3,0,0),false);
        agregarModificador("recibir",11,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/stand/hit/4.png"),3,0,0),false);
//        wizardAgregarImagenes(this,carpeta+"/stand/hit/",4,"recibir",grafico);

        setString("iniciar hadouken","");
        setEntero("hadouken posicion x",0);
        setEntero("hadouken posicion y",350);
        setImagen("hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/1.png"),3,0,0));
        hb_roja.clear();
        hb_roja.push_back(HitBox(-50,-50,50,50));
        setHitBoxes("hadouken hitboxes",hb_roja);
        setString("hadouken estado","");
        setString("hadouken orientacion","");
        agregarProyectil("hadouken","hadouken posicion x","hadouken posicion y","hadouken imagen","hadouken hitboxes","hadouken estado","hadouken orientacion");
        //agregarMovimiento("procesar hadouken");
        condicion.clear();
        condicion.push_back(Condicion("iniciar hadouken","=","activo",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("procesar hadouken",0,condicion);
        agregarModificador("procesar hadouken",0,"hadouken orientacion","d",false);
        agregarModificador("procesar hadouken",0,"iniciar hadouken","",false);
        agregarModificador("procesar hadouken",0,"hadouken estado","activo",false);
        agregarModificador("procesar hadouken",9,"hadouken estado","",false);
        agregarModificador("procesar hadouken",0,"daño fisico",-10,false,true);
        agregarModificador("procesar hadouken",9,"daño fisico",0,false,true);
        agregarModificador("procesar hadouken",0,"entero","hadouken posicion x","posicion_x",false,false);
        agregarModificador("procesar hadouken",0,"hadouken posicion x",125,true,false);
        for(int i=1;i<10;i++)
        {
            if(i%2==0)
                agregarModificador("procesar hadouken",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/1.png"),3,0,0),false);
            else
                agregarModificador("procesar hadouken",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/2.png"),3,0,0),false);
            agregarModificador("procesar hadouken",i,"hadouken posicion x",25,true,false);
        }

        setString("iniciar hadoukeni","");
        //agregarMovimiento("procesar hadoukeni");
        condicion.clear();
        condicion.push_back(Condicion("iniciar hadoukeni","=","activo",false));
        condicion.push_back(Condicion("hadouken estado","!=","activo",false));
        agregarCondicion("procesar hadoukeni",0,condicion);
        agregarModificador("procesar hadoukeni",0,"hadouken orientacion","i",false);
        agregarModificador("procesar hadoukeni",0,"iniciar hadoukeni","",false);
        agregarModificador("procesar hadoukeni",0,"hadouken estado","activo",false);
        agregarModificador("procesar hadoukeni",9,"hadouken estado","",false);
        agregarModificador("procesar hadoukeni",0,"daño fisico",-10,false,true);
        agregarModificador("procesar hadoukeni",9,"daño fisico",0,false,true);
        agregarModificador("procesar hadoukeni",0,"entero","hadouken posicion x","posicion_x",false,false);
        agregarModificador("procesar hadoukeni",0,"hadouken posicion x",-125,true,false);
        for(int i=1;i<10;i++)
        {
            if(i%2==0)
                agregarModificador("procesar hadoukeni",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/1.png"),3,0,0),false);
            else
                agregarModificador("procesar hadoukeni",i,"hadouken imagen",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/proyectiles/2.png"),3,0,0),false);
            agregarModificador("procesar hadoukeni",i,"hadouken posicion x",-25,true,false);
        }

        //agregarMovimiento("5 aereo");
        condicion.clear();
        condicion.push_back(Condicion("movimiento_actual","=","5",false));
        condicion.push_back(Condicion("saltando_lock","=","activo",false));
        agregarCondicion("5 aereo",0,condicion);
        agregarModificador("5 aereo",0,"imagen_personaje",Imagen(grafico->getTexture(carpeta+"/jump/idle/1.png"),3,0,0),false);

        //agregarMovimiento("separar");
        condicion.clear();
        condicion.push_back(Condicion("colision_hitboxes","=","si",false));
        condicion.push_back(Condicion("orientacion","=","d",false));
        agregarCondicion("separar",0,condicion);
        agregarModificador("separar",0,"posicion_x",-10,true,false);
        agregarModificador("separar",0,"posicion_x",10,true,true);

        //agregarMovimiento("separari");
        condicion.clear();
        condicion.push_back(Condicion("colision_hitboxes","=","si",false));
        condicion.push_back(Condicion("orientacion","=","i",false));
        agregarCondicion("separari",0,condicion);
        agregarModificador("separari",0,"posicion_x",10,true,false);
        agregarModificador("separari",0,"posicion_x",-10,true,true);
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
    Personaje *pa=(Personaje*)new RyuXml(Barra("hp_valor_maximo","hp_valor_actual","hp_modificador_periodico","hp_periodo",video::SColor(255,255,0,0),core::rect<s32>(0,0,200,50),NULL),300,350,2,"d",grafico,NULL,inputa);
    Personaje *pb=(Personaje*)new RyuXml(Barra("hp_valor_maximo","hp_valor_actual","hp_modificador_periodico","hp_periodo",video::SColor(255,255,0,0),core::rect<s32>(250,0,450,50),NULL),624,350,3,"i",grafico,NULL,inputb);

    //Menu m(stage,pa,pb,sonido,grafico,receiver);
    //m.loopMenu();

    Fighter fighter(stage,pa,pb,grafico,sonido);
    return 0;
}
