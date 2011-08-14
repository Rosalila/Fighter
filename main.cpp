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
        personaje->agregarModificador(movimiento,i,Imagen(grafico->getTexture(irr::io::path(str)),3,0,0),"imagen_personaje",false);
    }
}

class Ryu : Personaje
{
public:
    Ryu(Barra hp,int px,int py,int a,stringw orientacion,Grafico* grafico,Personaje *personaje_contrario,Input* input)
    {
        stringw carpeta="resources/Personajes/RyuSF2";
        this->input=input;
        setImagen("imagen_personaje",Imagen(grafico->getTexture("resources/Personajes/RyuSF2/stand/idle/1.png"),1,100,100));

        this->grafico=grafico;
        setString("estado_posicion","");
        setEntero("tiempo_transcurrido",0);
        setString("orientacion",orientacion);
        setString("movimiento_actual","5");

        enteros["posicion_x"]=px;
        enteros["posicion_y"]=py;

        barras["hp"]=hp;

        vector<HitBox> hb_vacia;
        hitboxes["azules"]=hb_vacia;
        hitboxes["rojas"]=hb_vacia;

        agregarMovimiento("5");
        agregarInput("5","5");
        for(int i=0;i<4;i++)
            agregarFrame("5",3);
        vector <HitBox> hb_roja;
        vector <HitBox> hb_azul;
        hb_azul.push_back(HitBox(-100,-100,100,100));
        agregarModificador("5",0,hb_azul,"azules",false);
        agregarCondicion("5",0,Condicion("6","movimiento_actual"));
        agregarCondicion("5",0,Condicion("4","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/stand/idle/",4,"5",grafico);

        agregarMovimiento("6");
        agregarInput("6","6");
        for(int i=0;i<5;i++)
            agregarFrame("6",3);
        agregarCondicion("6",0,Condicion("5","movimiento_actual"));
        for(int i=0;i<5;i++)
            agregarModificador("6",i,10,"posicion_x",true,false);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"6",grafico);

        agregarMovimiento("4");
        agregarInput("4","4");
        for(int i=0;i<5;i++)
            agregarFrame("4",3);
        agregarCondicion("4",0,Condicion("5","movimiento_actual"));
        for(int i=0;i<5;i++)
            agregarModificador("4",i,-10,"posicion_x",true,false);
        wizardAgregarImagenes(this,carpeta+"/stand/walking/",5,"4",grafico);

        agregarMovimiento("8");
        agregarInput("8","8");
        for(int i=0;i<7;i++)
            agregarFrame("8",3);
        agregarCondicion("8",0,Condicion("5","movimiento_actual"));
        agregarModificador("8",1,-50,"posicion_y",true,false);
        agregarModificador("8",2,-50,"posicion_y",true,false);
        agregarModificador("8",3,-30,"posicion_y",true,false);
        agregarModificador("8",4,30,"posicion_y",true,false);
        agregarModificador("8",5,50,"posicion_y",true,false);
        agregarModificador("8",6,50,"posicion_y",true,false);
        wizardAgregarImagenes(this,carpeta+"/jump/8/",7,"8",grafico);

        agregarMovimiento("68");
        agregarInput("68","68");
        for(int i=0;i<7;i++)
            agregarFrame("68",3);
        agregarCondicion("68",0,Condicion("5","movimiento_actual"));
        agregarModificador("68",1,-50,"posicion_y",true,false);
        agregarModificador("68",2,-50,"posicion_y",true,false);
        agregarModificador("68",3,-30,"posicion_y",true,false);
        agregarModificador("68",4,30,"posicion_y",true,false);
        agregarModificador("68",5,50,"posicion_y",true,false);
        agregarModificador("68",6,50,"posicion_y",true,false);

        agregarModificador("68",1,20,"posicion_x",true,false);
        agregarModificador("68",2,20,"posicion_x",true,false);
        agregarModificador("68",3,20,"posicion_x",true,false);
        agregarModificador("68",4,20,"posicion_x",true,false);
        agregarModificador("68",5,20,"posicion_x",true,false);
        agregarModificador("68",6,20,"posicion_x",true,false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"68",grafico);

        agregarMovimiento("48");
        agregarInput("48","48");
        for(int i=0;i<7;i++)
            agregarFrame("48",3);
        agregarCondicion("48",0,Condicion("5","movimiento_actual"));
        agregarModificador("48",1,-50,"posicion_y",true,false);
        agregarModificador("48",2,-50,"posicion_y",true,false);
        agregarModificador("48",3,-30,"posicion_y",true,false);
        agregarModificador("48",4,30,"posicion_y",true,false);
        agregarModificador("48",5,50,"posicion_y",true,false);
        agregarModificador("48",6,50,"posicion_y",true,false);

        agregarModificador("48",1,-20,"posicion_x",true,false);
        agregarModificador("48",2,-20,"posicion_x",true,false);
        agregarModificador("48",3,-20,"posicion_x",true,false);
        agregarModificador("48",4,-20,"posicion_x",true,false);
        agregarModificador("48",5,-20,"posicion_x",true,false);
        agregarModificador("48",6,-20,"posicion_x",true,false);
        wizardAgregarImagenes(this,carpeta+"/jump/9/",7,"48",grafico);

        agregarMovimiento("2");
        agregarInput("2","2");
        agregarInput("24","2");
        agregarInput("26","2");
        for(int i=0;i<1;i++)
            agregarFrame("2",3);
        agregarCondicion("2",0,Condicion("5","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/crouch/idle/",1,"2",grafico);

        agregarMovimiento("8a");
        agregarInput("a","8a");
        for(int i=0;i<3;i++)
            agregarFrame("8a",3);
        agregarCondicion("8a",0,Condicion("8","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/jump/8a 8b 8c/",3,"8a",grafico);

        agregarMovimiento("a");
        agregarInput("a","a");
        agregarInput("4a","a");
        agregarInput("6a","a");
        for(int i=0;i<3;i++)
            agregarFrame("a",3);
        agregarCondicion("a",0,Condicion("5","movimiento_actual"));
        agregarCondicion("a",0,Condicion("4","movimiento_actual"));
        agregarCondicion("a",0,Condicion("6","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/stand/a/",3,"a",grafico);

        agregarMovimiento("2a");
        agregarInput("2a","2a");
        agregarInput("24a","2a");
        agregarInput("26a","2a");
        for(int i=0;i<3;i++)
            agregarFrame("2a",3);
        agregarCondicion("2a",0,Condicion("2","movimiento_actual"));
        agregarCondicion("2a",0,Condicion("5","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/crouch/a/",3,"2a",grafico);

        agregarMovimiento("b");
        agregarInput("b","b");
        agregarInput("4b","b");
        agregarInput("6b","b");
        for(int i=0;i<5;i++)
            agregarFrame("b",3);
        agregarCondicion("b",0,Condicion("5","movimiento_actual"));
        agregarCondicion("b",0,Condicion("4","movimiento_actual"));
        agregarCondicion("b",0,Condicion("6","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/stand/b c/",5,"b",grafico);

        agregarMovimiento("2b");
        agregarInput("2b","2b");
        agregarInput("24b","2b");
        agregarInput("26b","2b");
        for(int i=0;i<4;i++)
            agregarFrame("2b",3);
        agregarCondicion("2b",0,Condicion("2","movimiento_actual"));
        agregarCondicion("2b",0,Condicion("5","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/crouch/b/",4,"2b",grafico);

        agregarMovimiento("c");
        agregarInput("c","c");
        agregarInput("4c","c");
        agregarInput("6c","c");
        for(int i=0;i<5;i++)
            agregarFrame("c",3);
        agregarCondicion("c",0,Condicion("5","movimiento_actual"));
        agregarCondicion("c",0,Condicion("4","movimiento_actual"));
        agregarCondicion("c",0,Condicion("6","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/stand/b c/",5,"c",grafico);

        agregarMovimiento("2c");
        agregarInput("2c","2c");
        agregarInput("24c","2c");
        agregarInput("26c","2c");
        for(int i=0;i<5;i++)
            agregarFrame("2c",3);
        agregarCondicion("2c",0,Condicion("2","movimiento_actual"));
        agregarCondicion("2c",0,Condicion("5","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/crouch/c/",5,"2c",grafico);

        agregarMovimiento("d");
        agregarInput("d","d");
        agregarInput("4d","d");
        agregarInput("6d","d");
        for(int i=0;i<3;i++)
            agregarFrame("d",3);
        agregarCondicion("d",0,Condicion("5","movimiento_actual"));
        agregarCondicion("d",0,Condicion("4","movimiento_actual"));
        agregarCondicion("d",0,Condicion("6","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/stand/d e/",3,"d",grafico);

        agregarMovimiento("2d");
        agregarInput("2d","2d");
        agregarInput("24d","2d");
        agregarInput("26d","2d");
        for(int i=0;i<3;i++)
            agregarFrame("2d",3);
        agregarCondicion("2d",0,Condicion("2","movimiento_actual"));
        agregarCondicion("2d",0,Condicion("5","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/crouch/d/",3,"2d",grafico);

        agregarMovimiento("e");
        agregarInput("e","e");
        agregarInput("4e","e");
        agregarInput("6e","e");
        for(int i=0;i<3;i++)
            agregarFrame("e",3);
        agregarCondicion("e",0,Condicion("5","movimiento_actual"));
        agregarCondicion("e",0,Condicion("4","movimiento_actual"));
        agregarCondicion("e",0,Condicion("6","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/stand/d e/",3,"e",grafico);

        agregarMovimiento("2e");
        agregarInput("2e","2e");
        agregarInput("24e","2e");
        agregarInput("26e","2e");
        for(int i=0;i<3;i++)
            agregarFrame("2e",3);
        agregarCondicion("2e",0,Condicion("2","movimiento_actual"));
        agregarCondicion("2e",0,Condicion("5","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/crouch/e/",3,"2e",grafico);

        agregarMovimiento("f");
        agregarInput("f","f");
        agregarInput("4f","f");
        agregarInput("6f","f");
        for(int i=0;i<5;i++)
            agregarFrame("f",3);
        agregarCondicion("f",0,Condicion("5","movimiento_actual"));
        agregarCondicion("f",0,Condicion("4","movimiento_actual"));
        agregarCondicion("f",0,Condicion("6","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/stand/f/",5,"f",grafico);

        agregarMovimiento("2f");
        agregarInput("2f","2f");
        agregarInput("24f","2f");
        agregarInput("26f","2f");
        for(int i=0;i<5;i++)
            agregarFrame("2f",3);
        agregarCondicion("2f",0,Condicion("2","movimiento_actual"));
        agregarCondicion("2f",0,Condicion("5","movimiento_actual"));
        wizardAgregarImagenes(this,carpeta+"/crouch/f/",5,"2f",grafico);
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
    botonesb.push_back(Boton(3,"b"));
    botonesb.push_back(Boton(5,"c"));
    botonesb.push_back(Boton(1,"d"));
    botonesb.push_back(Boton(2,"e"));
    botonesb.push_back(Boton(7,"f"));

    botonesa.push_back(Boton(irr::KEY_KEY_S,"2"));
    botonesa.push_back(Boton(irr::KEY_KEY_A,"4"));
    botonesa.push_back(Boton(irr::KEY_KEY_D,"6"));
    botonesa.push_back(Boton(irr::KEY_KEY_W,"8"));

    botonesa.push_back(Boton(irr::KEY_KEY_U,"a"));
    botonesa.push_back(Boton(irr::KEY_KEY_I,"b"));
    botonesa.push_back(Boton(irr::KEY_KEY_O,"c"));
    botonesa.push_back(Boton(irr::KEY_KEY_J,"d"));
    botonesa.push_back(Boton(irr::KEY_KEY_K,"e"));
    botonesa.push_back(Boton(irr::KEY_KEY_L,"f"));

    Input *inputb=new Input(botonesa,receiver);
    Input *inputa=new Input(botonesb,receiver);

    Grafico *grafico=new Grafico(receiver);
    Sonido *sonido = new Sonido();

    Stage *stage=new Stage(grafico->getTexture("resources/Stages/Stage02.png"),grafico->getTexture("resources/Stages/Barra_Vida.png"),grafico);

    Personaje *pb=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(250,0,450,50),NULL),400,150,3,"i",grafico,NULL,inputb);
    Personaje *pa=(Personaje*)new Ryu(Barra(250,250,-1,1,video::SColor(255,255,0,0),core::rect<s32>(0,0,200,50),NULL),100,150,2,"d",grafico,pb,inputa);

    //Menu m(stage,pa,pb,sonido,grafico,receiver);
    //m.loopMenu();

    Fighter fighter(stage,pa,pb,grafico,sonido);
    return 0;
}
