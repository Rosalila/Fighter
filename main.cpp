#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "include/Input.h"
#include "include/Fighter.h"


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
        personaje->agregarModificador(movimiento,i,Imagen(grafico->getTexture(irr::io::path(str)),0,0),"imagen_personaje",false);
    }
}

class Ryu : Personaje
{
public:
Ryu(Barra hp,int px,int py,int a,stringw orientacion,Grafico* grafico,Personaje *personaje_contrario,Input* input)
{
        this->input=input;
        setImagen("imagen_personaje",Imagen(grafico->getTexture("resources/Personajes/Ryu/Sprites/respirar/parado/1.png"),100,100,100,100));
        this->grafico=grafico;
        setString("estado_posicion","");
        setEntero("frame_actual_saltando",0);
        setEntero("tiempo_transcurrido",0);
        setString("orientacion",orientacion);
        setString("movimiento_actual","5");

        enteros["posicion_x"]=px;
        enteros["posicion_y"]=py;

        barras["hp"]=hp;

        vector<HitBox> hb_vacia;
        hitboxes["azules"]=hb_vacia;
        hitboxes["rojas"]=hb_vacia;

        //Creacion de movimientos
        agregarMovimiento("recibir");
        for(int i=0;i<4;i++)
            agregarFrame("recibir",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/recibir/arriba/",4,"recibir",grafico);

        agregarMovimiento("24");
        agregarMovimiento("2");
        agregarMovimiento("26");
        agregarMovimiento("4");
        for(int i=0;i<11;i++)
            agregarFrame("4",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/caminar/atras/",11,"4",grafico);
        agregarMovimiento("5");
        for(int i=0;i<10;i++)
            agregarFrame("5",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/respirar/parado/",10,"5",grafico);

        vector <HitBox> hb_roja;
        vector <HitBox> hb_azul;
        hb_azul.push_back(HitBox(-100,-100,100,100));
        agregarModificador("5",0,hb_azul,"azules",false);

        agregarMovimiento("6");
        for(int i=0;i<12;i++)
            agregarFrame("6",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/caminar/adelante/",12,"6",grafico);

        agregarMovimiento("48");
        for(int i=0;i<13;i++)
            agregarFrame("48",1);
        agregarModificador("48",0,"saltando_atras","estado_posicion",false);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/atras/",13,"48",grafico);

        agregarMovimiento("8");
        for(int i=0;i<12;i++)
            agregarFrame("8",1);
        agregarModificador("8",0,"saltando","estado_posicion",false);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/arriba/",12,"8",grafico);

        agregarMovimiento("68");
        for(int i=0;i<13;i++)
            agregarFrame("68",1);
        agregarModificador("68",0,"saltando_adelante","estado_posicion",false);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/adelante/",13,"68",grafico);

        agregarMovimiento("a");
        for(int i=0;i<5;i++)
            agregarFrame("a",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque1/",5,"a",grafico);

        agregarModificador("a",2,"recibir","movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("a",0,hb_roja,"rojas",false);
        hb_roja.clear();
        agregarModificador("a",4,hb_roja,"rojas",false);

        agregarMovimiento("b");
        for(int i=0;i<5;i++)
            agregarFrame("b",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque1/",5,"b",grafico);

        agregarModificador("b",2,"recibir","movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("b",0,hb_roja,"rojas",false);
        hb_roja.clear();
        agregarModificador("b",4,hb_roja,"rojas",false);

        agregarMovimiento("c");
        for(int i=0;i<5;i++)
            agregarFrame("c",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque1/",5,"c",grafico);

        agregarModificador("c",2,"recibir","movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("c",0,hb_roja,"rojas",false);
        hb_roja.clear();
        agregarModificador("c",4,hb_roja,"rojas",false);

        agregarMovimiento("d");
        for(int i=0;i<5;i++)
            agregarFrame("d",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque1/",5,"d",grafico);

        agregarModificador("d",2,"recibir","movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("d",0,hb_roja,"rojas",false);
        hb_roja.clear();
        agregarModificador("d",4,hb_roja,"rojas",false);

        agregarMovimiento("ab");
        for(int i=0;i<14;i++)
            agregarFrame("ab",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/agarre/",14,"ab",grafico);

        agregarMovimiento("cd");
        for(int i=0;i<7;i++)
            agregarFrame("cd",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/overhead/",7,"cd",grafico);


        agregarMovimiento("hadouken");
        for(int i=0;i<14;i++)
            agregarFrame("hadouken",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/especial/hadouken/",14,"hadouken",grafico);


        for(int i=0;i<11;i++)
            agregarModificador("4",i,-10,"posicion_x",true,false);
        for(int i=0;i<12;i++)
            agregarModificador("6",i,10,"posicion_x",true,false);

        //cancels
        agregarCancel("a","5");
        agregarCancel("b","5");
        agregarCancel("c","5");
        agregarCancel("d","5");
        agregarCancel("ab","5");
        agregarCancel("cd","5");
        agregarCancel("hadouken","5");
        agregarCancel("4","5");
        agregarCancel("6","5");
        agregarCancel("48","5");
        agregarCancel("8","5");
        agregarCancel("68","5");

        agregarCancel("a","4");
        agregarCancel("b","4");
        agregarCancel("c","4");
        agregarCancel("d","4");
        agregarCancel("ab","4");
        agregarCancel("cd","4");
        agregarCancel("hadouken","4");
        agregarCancel("5","4");
        agregarCancel("6","4");
        //
        agregarCancel("a","6");
        agregarCancel("b","6");
        agregarCancel("c","6");
        agregarCancel("d","6");
        agregarCancel("ab","6");
        agregarCancel("cd","6");
        agregarCancel("hadouken","6");
        agregarCancel("4","6");
        agregarCancel("5","6");
    }
};

int main()
{
    Receiver* receiver=new Receiver();

    vector<Boton> botonesa,botonesb;

    botonesb.push_back(Boton(-2,"2"));
    botonesb.push_back(Boton(-4,"4"));
    botonesb.push_back(Boton(-6,"6"));
    botonesb.push_back(Boton(-8,"8"));

    botonesb.push_back(Boton(0,"a"));
    botonesb.push_back(Boton(1,"b"));
    botonesb.push_back(Boton(2,"c"));
    botonesb.push_back(Boton(3,"d"));

    botonesa.push_back(Boton(irr::KEY_KEY_S,"2"));
    botonesa.push_back(Boton(irr::KEY_KEY_A,"4"));
    botonesa.push_back(Boton(irr::KEY_KEY_D,"6"));
    botonesa.push_back(Boton(irr::KEY_KEY_W,"8"));

    botonesa.push_back(Boton(irr::KEY_KEY_U,"a"));
    botonesa.push_back(Boton(irr::KEY_KEY_I,"b"));
    botonesa.push_back(Boton(irr::KEY_KEY_J,"c"));
    botonesa.push_back(Boton(irr::KEY_KEY_K,"d"));

    Input *inputa=new Input(botonesa,receiver);
    Input *inputb=new Input(botonesb,receiver);

    Grafico *grafico=new Grafico(receiver);
    Sonido *sonido = new Sonido();

    Stage *stage=new Stage(grafico->getTexture("resources/Stages/Stage02.png"),grafico->getTexture("resources/Stages/Barra_Vida.png"),grafico);

    Personaje *pb=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(250,0,450,50),NULL),800,300,3,"i",grafico,NULL,inputb);
    Personaje *pa=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(0,0,200,50),NULL),50,300,2,"d",grafico,pb,inputa);

    //Menu m(stage,pa,pb,sonido,grafico,receiver);
    //m.loopMenu();

    Fighter fighter(stage,pa,pb,grafico,sonido);
    return 0;
}
