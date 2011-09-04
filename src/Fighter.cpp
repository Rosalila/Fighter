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
    sonido->agregarSonido("Fondo","resources/Stages/Sonidos/Fondo.ogg");
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


bool Fighter::getColisionHitBoxes(Personaje *atacante,stringw variable_atacante,Personaje* atacado,stringw variable_atacado)
{
    vector <HitBox> hb_azules=atacado->getHitBoxes(variable_atacado);
    vector <HitBox> hb_rojas=atacante->getHitBoxes(variable_atacante);

    if(atacante->getString("orientacion")=="i")
    for(int i=0;i<(int)hb_rojas.size();i++)
    {
        int a=hb_rojas[i].p1x;
        int b=hb_rojas[i].p2x;
        hb_rojas[i].p1x=-b;
        hb_rojas[i].p2x=-a;
    }
    if(atacado->getString("orientacion")=="i")
    for(int i=0;i<(int)hb_azules.size();i++)
    {
        int a=hb_azules[i].p1x;
        int b=hb_azules[i].p2x;
        hb_azules[i].p1x=-b;
        hb_azules[i].p2x=-a;
    }


    int ax=atacado->getEntero("posicion_x");
    int ay=atacado->getEntero("posicion_y");
    int rx=atacante->getEntero("posicion_x");
    int ry=atacante->getEntero("posicion_y");

    for(int a=0;a<(int)hb_azules.size();a++)
        for(int r=0;r<(int)hb_rojas.size();r++)
            if(getColisionHitBoxes(hb_azules[a],hb_rojas[r],ax,ay,rx,ry))
                return true;
    return false;
}

void Fighter::logicaPersonaje(Personaje* p)
{
    //verificar colision de hitboxes
    if(getColisionHitBoxes(p->personaje_contrario,"rojas",p,"azules"))
        p->setString("colision_hitboxes","si");
    else
        p->setString("colision_hitboxes","no");

    if(getColisionHitBoxes(p->personaje_contrario,"azules",p,"azules"))
        p->setString("colision_hitboxes_azules","si");
    else
        p->setString("colision_hitboxes_azules","no");
    //verificar flip
    if(p->getEntero("posicion_x")>p->personaje_contrario->getEntero("posicion_x"))
        p->strings["orientacion"]="i";
    else
        p->strings["orientacion"]="d";
    //get input
    stringw str_movimiento=p->mapInputToMovimiento();
    //ejecutar cancel
    if(str_movimiento!="")
    if(p->cumpleCondiciones(str_movimiento))
    {
        Movimiento* m=p->movimientos[p->getString("movimiento_actual")];
        m->frame_actual=0;
        m->tiempo_transcurrido=0;
        p->setString("movimiento_actual",str_movimiento);
    }
    //Movimientos continuos
      //agregar nuevos
    for(int i=0;i<(int)p->inputs.size();i++)//for each movimiento
        if(p->inputs[i].input[0]=="*")//buscar los constantes
            if(p->cumpleCondiciones(p->inputs[i].movimiento))//si cumple
            {
                bool existe=false;
                for(int j=0;j<(int)p->movimientos_constantes_actuales.size();j++)//for each movimiento
                    if(p->movimientos_constantes_actuales[j]->nombre==p->inputs[i].movimiento)
                    {
                        existe=true;
                    }
                if(!existe)
                    p->movimientos_constantes_actuales.push_back(p->movimientos[p->inputs[i].movimiento]);
            }

}

void Fighter::aplicarModificadores(Personaje *p)
{
    //get movimiento y frame
    Movimiento* m=p->movimientos[p->getString("movimiento_actual")];
    Frame* f=&m->frames[m->frame_actual];
    //aplicar modificadores
    if(m->tiempo_transcurrido==0)
        p->aplicarModificadores(f->modificadores);
    //avanzar frame
    if(m->tiempo_transcurrido==f->duracion)
    {
        m->frame_actual++;
        m->tiempo_transcurrido=0;
    }else
        m->tiempo_transcurrido++;
    //verificar fin de movimiento
    if(m->frame_actual==(int)m->frames.size())
    {
        m->frame_actual=0;
        p->setString("movimiento_actual","5");
    }
    //Movimientos continuos
      //ejecutar existentes
    for(int i=0;i<(int)p->movimientos_constantes_actuales.size();i++)
    {
        Movimiento* mc=p->movimientos_constantes_actuales[i];
        Frame* fc=&mc->frames[mc->frame_actual];
        if(mc->tiempo_transcurrido==0)
            p->aplicarModificadores(fc->modificadores);
        //avanzar frame
        if(mc->tiempo_transcurrido==fc->duracion)
        {
            mc->frame_actual++;
            mc->tiempo_transcurrido=0;
        }else
            mc->tiempo_transcurrido++;
        //verificar fin de movimiento
        if(mc->frame_actual==(int)mc->frames.size())
        {
            mc->frame_actual=0;
            p->movimientos_constantes_actuales.erase(p->movimientos_constantes_actuales.begin()+i);
        }
    }
}

void Fighter::logica()
{
    logicaPersonaje(pa);
    logicaPersonaje(pb);
    aplicarModificadores(pa);
    aplicarModificadores(pb);
}

void Fighter::loopJuego()
{
    //sonido->reproducirSonido("Fight!");
    //sonido->reproducirSonido("Fondo");
	for (;!pa->input->receiver->IsKeyDown(irr::KEY_RETURN);)
	{
	    if(pa->input->receiver->IsKeyDown(irr::KEY_ESCAPE))
            exit(0);
	    if(pa->getEntero("hp_valor_actual")<=0 || pb->getEntero("hp_valor_actual")<=0)
            break;
	    //setear frames a "60"
	    grafico->device->getTimer()->start();
	    for(u32 t=grafico->device->getTimer()->getTime();
            t+16>grafico->device->getTimer()->getTime();
            grafico->device->getTimer()->tick()
         );
        //logica
        logica();

        //render
        render(pa,pb,stage);
	}
	//game over
	irr::video::ITexture* texture_game_over=grafico->getTexture("resources/ko.jpg");
	for(;!pa->input->receiver->IsKeyDown(irr::KEY_RETURN);)
	{
	    if(pa->input->receiver->IsKeyDown(irr::KEY_ESCAPE))
            exit(0);
        if (grafico->isWindowActive())
        {
            grafico->beginScene();
            grafico->draw2DImage
            (   texture_game_over,
                irr::core::dimension2d<irr::f32> (grafico->ventana_x,grafico->ventana_y),
                irr::core::rect<irr::f32>(0,0,grafico->ventana_x,grafico->ventana_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (0,0),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->endScene();
        }
        grafico->run();
	}
}

void itoa(int n, char *s, int b) {
	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i=0, sign;

	if ((sign = n) < 0)
		n = -n;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	//return strrev(s);
}

char *strrev(char *str) {
	char *p1, *p2;

	if (!str || !*str)
		return str;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
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
        pa->dibujarHitBoxes("azules","resources/blue.png",pa->getString("orientacion")=="i");
        pb->dibujarHitBoxes("azules","resources/blue.png",pb->getString("orientacion")=="i");
        pa->dibujarHitBoxes("rojas","resources/red.png",pa->getString("orientacion")=="i");
        pb->dibujarHitBoxes("rojas","resources/red.png",pb->getString("orientacion")=="i");

        pa->dibujarProyectiles();
        pb->dibujarProyectiles();
//
//
        //Movimento actual
        //grafico->drawText(pa->getString("movimiento_actual"),irr::core::rect<irr::s32>(50,50,500,500),irr::video::ECP_GREEN);

//        stringw str=pa->getString("movimiento_actual")+","+pa->getString("estado_posicion")+": ";
//        for(int i=0;i<(int)pa->input->getBufferInputs().size();i++)
//            str+=pa->input->getBufferInputs()[i]+"-";
//        grafico->device->setWindowCaption(str.c_str());
//        grafico->device->setWindowCaption(pb->getString("colision_hitboxes").c_str());
//	int num = pa->getEntero("posicion_y");
//	char buf[5];

	// convert 123 to string [buf]
//	itoa(num, buf, 10);
//	stringw str(strrev(buf));
//grafico->device->setWindowCaption(str.c_str());
        //grafico->device->setWindowCaption((pa->getEntero("posicion_x")+","+pa->getEntero("posicion_y")).c_str());

//
//        //grafico->draw2DRectangle(SColor(1000,0,100,0),core::rect<s32>(pa->getEntero("posicion_x"),pa->getEntero("posicion_y"),pa->getEntero("posicion_x")+100,pa->getEntero("posicion_y")+100));
//
//        int dimension_x=50;
//        int dimension_y=50;
//        grafico->draw2DImage
//    (   grafico->getTexture("resources/green.png"),
//        irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
//        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
//        irr::core::position2d<irr::f32>(pa->getEntero("posicion_x"),pa->getEntero("posicion_y")),
//        irr::core::position2d<irr::f32>(0,0),
//        irr::f32(0), irr::core::vector2df (1,1),
//        true,
//        irr::video::SColor(255,255,255,255),
//        false,
//        false);

        //grafico->draw2DRectangle(SColor(1000,0,100,0),core::rect<s32>(0,0,1000,1000));
        grafico->endScene();
    }
    return grafico->run();
    //return true;
}


