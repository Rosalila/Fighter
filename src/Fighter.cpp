#include "../include/Fighter.h"
Fighter::Fighter(Stage* stage,Personaje*pa,Personaje*pb,Grafico *grafico,Sonido *sonido)
{
    //Engines
    this->grafico=grafico;
    this->sonido=sonido;

    //Sets
    this->stage=stage;
    this->pa=pa;
    this->pb=pb;
    pa->personaje_contrario=pb;
    pb->personaje_contrario=pa;

    sonido->agregarSonido("Fight!","resources/Stages/Sonidos/Fight1.wav");
    sonido->agregarSonido("Fondo","resources/Stages/Sonidos/Now.ogg");
    sonido->agregarSonido("Fondo2","resources/Stages/Sonidos/Something like this.mp3");

    //Menu
    //loopMenu();

    //Juego
    loopJuego();

    //Drops
    sonido->drop(); // delete engine
}

bool Fighter::getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
    int x1r=hb_roja.p1x+atacante_x;
    int y1r=hb_roja.p1y+atacante_y;
    int x2r=hb_roja.p2x+atacante_x;
    int y2r=hb_roja.p2y+atacante_y;

    int x1a=hb_azul.p1x+atacado_x;
    int y1a=hb_azul.p1y+atacado_y;
    int x2a=hb_azul.p2x+atacado_x;
    int y2a=hb_azul.p2y+atacado_y;

    return (
            (x1r<=x1a && x1a<=x2r && x2r<=x2a) ||
            (x1r<=x1a && x1a<=x2a && x2a<=x2r) ||
            (x1a<=x1r && x1r<=x2r && x2r<=x2a) ||
            (x1a<=x1r && x1r<=x2a && x2a<=x2r)
            )&&(
            (y1r<=y1a && y1a<=y2r && y2r<=y2a) ||
            (y1r<=y1a && y1a<=y2a && y2a<=y2r) ||
            (y1a<=y1r && y1r<=y2r && y2r<=y2a) ||
            (y1a<=y1r && y1r<=y2a && y2a<=y2r)
            );
}


bool Fighter::getColisionHitBoxes(Personaje *atacante,Personaje* atacado)
{
    int ax=atacado->getEntero("posicion_x");
    int ay=atacado->getEntero("posicion_y");
    int rx=atacante->getEntero("posicion_x");
    int ry=atacante->getEntero("posicion_y");

    int hb_azul_size=atacado->getHitBoxes("azules").size();
    int hb_roja_size=atacante->getHitBoxes("rojas").size();
    for(int a=0;a<hb_azul_size;a++)
        for(int r=0;r<hb_roja_size;r++)
            if(getColisionHitBoxes(atacado->getHitBoxes("azules")[a],atacante->getHitBoxes("rojas")[r],ax,ay,rx,ry))
                return true;
    return false;
}

void Fighter::loopJuego()
{
    sonido->reproducirSonido("Fight!");
    sonido->reproducirSonido("Fondo");
	for (;;)
	{
        render(pa,pb,stage);
        logica(pa,pa->input->getInput());
        logica(pb,pb->input->getInput());
	}
}

void Fighter::logica(Personaje* personaje,stringw input)
{
    input=personaje->getString("estado_posicion")+input;

    //flipear personaje
    if(personaje->getEntero("posicion_x")>personaje->personaje_contrario->getEntero("posicion_x"))
    {
        personaje->strings["orientacion"]="i";
        if(input=="4")
            input="6";
        else if(input=="6")
            input="4";
    }
    else
        personaje->strings["orientacion"]="d";
    //avanzar tiempo ++
    personaje->setEntero("tiempo_transcurrido",personaje->getEntero("tiempo_transcurrido")+1);
    //si se termino
    personaje->verificarFinDeMovimiento();
    //si hay cancel, cambiar input
    personaje->ejectuarCancel(input);
    //modificadores
    personaje->aplicarModificadores();
}

bool Fighter::render(Personaje* pa,Personaje* pb,Stage* stage)
{
    if (grafico->isWindowActive())
    {
        grafico->beginScene();
        //Stage
        stage->dibujar();

        //Personaje
        pa->dibujar();
        pb->dibujar();

        //HP
        pa->dibujarBarra("hp");
        pb->dibujarBarra("hp");

        //Hit Boxes
        /*
        pa->dibujarHitBoxes("azules",video::SColor(100,0,0,255),pa->getString("orientacion")=="i");
        pb->dibujarHitBoxes("azules",video::SColor(100,0,0,255),pb->getString("orientacion")=="i");
        pa->dibujarHitBoxes("rojas",video::SColor(100,255,0,0),pa->getString("orientacion")=="i");
        pb->dibujarHitBoxes("rojas",video::SColor(100,255,0,0),pb->getString("orientacion")=="i");
        */

        //Movimento actual
        //grafico->drawText(pa->getString("movimiento_actual"),irr::core::rect<irr::s32>(50,50,500,500),irr::video::ECP_GREEN);
        stringw str="";
        for(int i=0;i<(int)pb->input->getBufferInputs().size();i++)
            str+=pb->input->getBufferInputs()[i]+"-";
        grafico->device->setWindowCaption(str.c_str());

        grafico->endScene();
    }
    return grafico->run();
    //return true;
}


