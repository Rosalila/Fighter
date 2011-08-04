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
        personaje->agregarModificador(movimiento,i,Imagen(grafico->getTexture(irr::io::path(str)),0,0),personaje,"imagen_personaje",false);
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
        //wizardMovimiento(this,"5",10,1,"resources/Personajes/Ryu/Sprites/respirar/01.png",grafico);
        agregarMovimiento("5");
        for(int i=0;i<10;i++)
            agregarFrame("5",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/respirar/parado/",10,"5",grafico);

        vector <HitBox> hb_roja;
        vector <HitBox> hb_azul;
        hb_azul.push_back(HitBox(-100,-100,100,100));
        //hb_roja.push_back(HitBox(60,80,80,120));
        agregarModificador("5",0,hb_azul,this,"azules",false);
        //personaje->agregarModificador(movimiento,i,hb_roja,personaje,"rojas",false);


        //wizardMovimiento(this,"6",12,1,"resources/Personajes/Ryu/Sprites/mover/caminar/adelante/01.png",grafico);
        agregarMovimiento("6");
        for(int i=0;i<12;i++)
            agregarFrame("6",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/caminar/adelante/",12,"6",grafico);

        agregarMovimiento("48");
        for(int i=0;i<13;i++)
            agregarFrame("48",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/atras/",13,"48",grafico);

        agregarMovimiento("8");
        for(int i=0;i<12;i++)
            agregarFrame("8",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/arriba/",12,"48",grafico);

        agregarMovimiento("68");

        agregarMovimiento("a");
        for(int i=0;i<5;i++)
            agregarFrame("a",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque1/",5,"a",grafico);

        agregarModificador("a",2,"recibir",this,"movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("a",0,hb_roja,this,"rojas",false);
        hb_roja.clear();
        agregarModificador("a",4,hb_roja,this,"rojas",false);

        agregarMovimiento("b");
        for(int i=0;i<14;i++)
            agregarFrame("b",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/agarre/",14,"b",grafico);

        agregarMovimiento("c");
        for(int i=0;i<7;i++)
            agregarFrame("c",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/overhead/",7,"c",grafico);

        agregarModificador("c",2,"recibir",this,"movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("c",0,hb_roja,this,"rojas",false);
        hb_roja.clear();
        agregarModificador("c",4,hb_roja,this,"rojas",false);

        agregarMovimiento("d");
        for(int i=0;i<5;i++)
            agregarFrame("d",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque1/",5,"d",grafico);

        agregarModificador("d",2,"recibir",this,"movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("d",0,hb_roja,this,"rojas",false);
        hb_roja.clear();
        agregarModificador("d",4,hb_roja,this,"rojas",false);

        agregarMovimiento("agachado24");
        for(int i=0;i<5;i++)
            agregarFrame("agachado24",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/respirar/agachado/",5,"agachado24",grafico);

        agregarMovimiento("agachado2");
        for(int i=0;i<5;i++)
            agregarFrame("agachado2",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/respirar/agachado/",5,"agachado2",grafico);

        agregarMovimiento("agachado26");
        for(int i=0;i<5;i++)
            agregarFrame("agachado26",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/respirar/agachado/",5,"agachado26",grafico);

        agregarMovimiento("agachado4");
        agregarMovimiento("agachado5");
        agregarMovimiento("agachado6");
        agregarMovimiento("agachado48");
        agregarMovimiento("agachado8");
        agregarMovimiento("agachado68");

        agregarMovimiento("agachadoa");
        for(int i=0;i<7;i++)
            agregarFrame("agachadoa",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/",7,"agachadoa",grafico);

        agregarModificador("agachadoa",2,"recibir",this,"movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("agachadoa",0,hb_roja,this,"rojas",false);
        hb_roja.clear();
        agregarModificador("agachadoa",4,hb_roja,this,"rojas",false);

        agregarMovimiento("agachadob");
        for(int i=0;i<7;i++)
            agregarFrame("agachadob",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/",7,"agachadob",grafico);

        agregarMovimiento("agachadoc");
        for(int i=0;i<7;i++)
            agregarFrame("agachadoc",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/",7,"agachadoc",grafico);

        agregarMovimiento("agachadod");
        for(int i=0;i<7;i++)
            agregarFrame("agachadod",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/golpe_bajo/",7,"agachadod",grafico);

        agregarMovimiento("saltando_atras24");
        agregarMovimiento("saltando_atras2");
        agregarMovimiento("saltando_atras26");
        agregarMovimiento("saltando_atras4");
        agregarMovimiento("saltando_atras5");
        agregarMovimiento("saltando_atras6");

        agregarMovimiento("saltando_atras48");
        for(int i=0;i<13;i++)
            agregarFrame("saltando_atras48",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/atras/",13,"saltando_atras48",grafico);

        agregarMovimiento("saltando_atras8");
        agregarMovimiento("saltando_atras68");

        agregarMovimiento("saltando_atrasa");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_atrasa",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_atrasa",grafico);

        agregarModificador("saltando_atrasa",2,"recibir",this,"movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("saltando_atrasa",0,hb_roja,this,"rojas",false);
        hb_roja.clear();
        agregarModificador("saltando_atrasa",4,hb_roja,this,"rojas",false);

        agregarMovimiento("saltando_atrasb");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_atrasb",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_atrasb",grafico);

        agregarMovimiento("saltando_atrasc");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_atrasc",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_atrasc",grafico);

        agregarMovimiento("saltando_atrasd");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_atrasd",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_atrasd",grafico);

        agregarMovimiento("saltando24");
        agregarMovimiento("saltando2");
        agregarMovimiento("saltando26");
        agregarMovimiento("saltando4");
        agregarMovimiento("saltando5");
        //wizardMovimiento(this,"saltando5",12,1,"resources/Personajes/Ryu/Sprites/mover/saltar/arriba/01.png",grafico);
        agregarMovimiento("saltando6");
        agregarMovimiento("saltando48");

        agregarMovimiento("saltando8");
        for(int i=0;i<12;i++)
            agregarFrame("saltando8",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/arriba/",12,"saltando8",grafico);

        agregarMovimiento("saltando68");

        agregarMovimiento("saltandoa");
        for(int i=0;i<6;i++)
            agregarFrame("saltandoa",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltandoa",grafico);

        agregarModificador("saltandoa",2,"recibir",this,"movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("saltandoa",0,hb_roja,this,"rojas",false);
        hb_roja.clear();
        agregarModificador("saltandoa",4,hb_roja,this,"rojas",false);

        agregarMovimiento("saltandob");
        for(int i=0;i<6;i++)
            agregarFrame("saltandob",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltandob",grafico);

        agregarMovimiento("saltandoc");
        for(int i=0;i<6;i++)
            agregarFrame("saltandoc",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltandoc",grafico);

        agregarMovimiento("saltandod");
        for(int i=0;i<6;i++)
            agregarFrame("saltandod",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltandod",grafico);

        agregarMovimiento("saltando_adelante24");
        agregarMovimiento("saltando_adelante2");
        agregarMovimiento("saltando_adelante26");
        agregarMovimiento("saltando_adelante4");
        agregarMovimiento("saltando_adelante5");
        //wizardMovimiento(this,"saltando_adelante5",13,1,"resources/Personajes/Ryu/Sprites/mover/saltar/adelante/01.png",grafico);
        agregarMovimiento("saltando_adelante6");
        agregarMovimiento("saltando_adelante48");
        agregarMovimiento("saltando_adelante8");

        agregarMovimiento("saltando_adelante68");
        for(int i=0;i<13;i++)
            agregarFrame("saltando_adelante68",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/mover/saltar/adelante/",13,"saltando_adelante68",grafico);

        agregarMovimiento("saltando_adelantea");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_adelantea",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_adelantea",grafico);

        agregarModificador("saltando_adelantea",2,"recibir",this,"movimiento_actual",true);
        hb_roja.clear();
        hb_roja.push_back(HitBox(-100,-100,100,100));
        agregarModificador("saltando_adelantea",0,hb_roja,this,"rojas",false);
        hb_roja.clear();
        agregarModificador("saltando_adelantea",4,hb_roja,this,"rojas",false);

        agregarMovimiento("saltando_adelanteb");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_adelanteb",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_adelanteb",grafico);

        agregarMovimiento("saltando_adelantec");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_adelantec",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_adelantec",grafico);

        agregarMovimiento("saltando_adelanted");
        for(int i=0;i<6;i++)
            agregarFrame("saltando_adelanted",1);
        wizardAgregarImagenes(this,"resources/Personajes/Ryu/Sprites/atacar/ataque_aereo/",6,"saltando_adelanted",grafico);


        for(int i=0;i<11;i++)
            agregarModificador("4",i,-10,this,"posicion_x",true,false);
        for(int i=0;i<12;i++)
            agregarModificador("6",i,10,this,"posicion_x",true,false);

        //cancels
        agregarCancel("a","5");
        agregarCancel("b","5");
        agregarCancel("c","5");
        agregarCancel("d","5");
        agregarCancel("agachado24","5");
        agregarCancel("agachado2","5");
        agregarCancel("agachado26","5");
        agregarCancel("4","5");
        agregarCancel("6","5");
        agregarCancel("saltando_atras48","5");
        agregarCancel("saltando8","5");
        agregarCancel("saltando_adelante68","5");

        agregarCancel("a","4");
        agregarCancel("b","4");
        agregarCancel("c","4");
        agregarCancel("d","4");
        agregarCancel("agachado24","4");
        agregarCancel("agachado2","4");
        agregarCancel("agachado26","4");
        agregarCancel("5","4");
        agregarCancel("6","4");
        agregarCancel("saltando_atras48","4");
        agregarCancel("saltando8","4");
        agregarCancel("saltando_adelante68","4");
        //
        agregarCancel("a","6");
        agregarCancel("b","6");
        agregarCancel("c","6");
        agregarCancel("d","6");
        agregarCancel("agachado24","6");
        agregarCancel("agachado2","6");
        agregarCancel("agachado26","6");
        agregarCancel("4","6");
        agregarCancel("5","6");
        agregarCancel("saltando_atras48","6");
        agregarCancel("saltando8","6");
        agregarCancel("saltando_adelante68","6");

        //saltar
        agregarCancel("saltando_atrasa","saltando_atras48");
        agregarCancel("saltandoa","saltando8");
        agregarCancel("saltando_adelantea","saltando_adelante68");

        agregarCancel("saltando_atrasb","saltando_atras48");
        agregarCancel("saltandob","saltando8");
        agregarCancel("saltando_adelanteb","saltando_adelante68");

        agregarCancel("saltando_atrasc","saltando_atras48");
        agregarCancel("saltandoc","saltando8");
        agregarCancel("saltando_adelantec","saltando_adelante68");

        agregarCancel("saltando_atrasd","saltando_atras48");
        agregarCancel("saltandod","saltando8");
        agregarCancel("saltando_adelanted","saltando_adelante68");
        //agachar
        agregarCancel("agachadoa","agachado24");
        agregarCancel("agachadob","agachado24");
        agregarCancel("agachadoc","agachado24");
        agregarCancel("agachadod","agachado24");
        agregarCancel("agachadoa","agachado2");
        agregarCancel("agachadob","agachado2");
        agregarCancel("agachadoc","agachado2");
        agregarCancel("agachadod","agachado2");
        agregarCancel("agachadoa","agachado26");
        agregarCancel("agachadob","agachado26");
        agregarCancel("agachadoc","agachado26");
        agregarCancel("agachadod","agachado126");
    }
};

int main()
{
    Receiver* receiver=new Receiver();



    Input *inputa=new Input(1,receiver);
    Input *inputb=new Input("a",receiver);

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
