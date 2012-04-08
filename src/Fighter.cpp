#include "../include/Fighter.h"
Fighter::Fighter(Sonido* sonido,Grafico* grafico,Receiver* receiver,vector<Personaje*>pa,vector<Personaje*>pb,Stage*stage)
{
    duracion_ko=30;
    tiempo_actual_ko=0;
    pos_imagen_ko=0;
    ko.push_back(Imagen(grafico->getTexture("misc/ko/1.png"),1,0,0));
    ko.push_back(Imagen(grafico->getTexture("misc/ko/2.png"),1,0,0));
    ko.push_back(Imagen(grafico->getTexture("misc/ko/3.png"),1,0,0));


    duracion_intro=30;
    tiempo_actual_intro=0;
    pos_imagen_intro=0;
    match_intro.push_back(Imagen(grafico->getTexture("misc/match_intro/1.png"),1,0,0));
    match_intro.push_back(Imagen(grafico->getTexture("misc/match_intro/2.png"),1,0,0));
    match_intro.push_back(Imagen(grafico->getTexture("misc/match_intro/3.png"),1,0,0));

    for(int i=0;i<(int)pa.size();i++)
        pa[i]->stage_piso=stage->pos_piso;
    for(int i=0;i<(int)pb.size();i++)
        pb[i]->stage_piso=stage->pos_piso;
//    //Creadas abierto
//    receiver=new Receiver();
//    //this->inputa=(Input*)new InputXml(1,receiver);
//    //this->inputb=(Input*)new InputXml(2,receiver);
//    this->inputa=new Input();
//    this->inputb=new Input();
//    //this->inputa->cargarIAXML(1);
//    this->inputa->cargarDesdeXML(1,receiver);
//    this->inputb->cargarDesdeXML(2,receiver);
//
//
//    //Parte de la clase
//    this->grafico=new Grafico(receiver);
//    this->sonido = new Sonido();
    //Engines
    this->sonido=sonido;
    this->grafico=grafico;
    this->receiver=receiver;
    //stage=new Stage(grafico,sonido);

    //stage->cargarDesdeXML((char*)"Stage1");
    pos_stage=0;
    //this->stage=(Stage*)new StageXml(grafico,(char*)"stages/Stage1/Stage1.xml");
    this->pa_actual=0;
    this->pb_actual=0;

//    Personaje*
//    setPaActual(new Personaje(grafico,sonido,1));
//    setPbActual(new Personaje(grafico,sonido,2));

    //menu=new Menu(grafico,receiver,sonido,(char*)"menu/main_menu.xml");
    pause_menu=new Menu(grafico,receiver,sonido,(char*)"menu/pause_menu.xml");

    //escribirInputsXML();


//        menu->pa.clear();
//        menu->pb.clear();
//
//        menu->loopMenu();
//        if(menu->getExitSignal())
//            exit(0);
//
//        pa.clear();
//        pa.push_back(menu->pa[0]);
//        if(menu->pa.size()>=2)
//            pa.push_back(menu->pa[1]);
//        if(menu->pa.size()==3)
//            pa.push_back(menu->pa[2]);
//
//        pb.clear();
//        pb.push_back(menu->pb[0]);
//        if(menu->pb.size()>=2)
//            pb.push_back(menu->pb[1]);
//        if(menu->pb.size()==3)
//            pb.push_back(menu->pb[2]);
//
////        setPaActual(menu->pa[0]);
////        setPbActual(menu->pb[0]);
//        stage=menu->stage;
//        inputa=menu->inputa;
//        inputb=menu->inputb;
        pos_stage=0;
        this->pa=pa;
        this->pb=pb;
        this->stage=stage;
        //Juego
        pa[0]->setString("current_move","intro");
        pb[0]->setString("current_move","intro");
        loopJuego();
}

Personaje* Fighter::getPaActual()
{
    return pa[pa_actual];
}

Personaje* Fighter::getPbActual()
{
    return pb[pb_actual];
}

Personaje* Fighter::get2doPa()
{
    if(pa_actual==(int)pa.size()-1)
        return pa[0];
    return pa[pa_actual+1];
}

Personaje* Fighter::get2doPb()
{
    if(pb_actual==(int)pb.size()-1)
        return pb[0];
    return pb[pb_actual+1];
}

Personaje* Fighter::get3erPa()
{
    if(pa_actual==(int)pa.size()-2)
        return pa[0];
    if(pa_actual==(int)pa.size()-1)
        return pa[1];
    return pa[pa_actual+2];
}

Personaje* Fighter::get3erPb()
{
    if(pb_actual==(int)pb.size()-2)
        return pb[0];
    if(pb_actual==(int)pb.size()-1)
        return pb[1];
    return pb[pb_actual+2];
}

void Fighter::setPaActual(Personaje* p)
{
    if(pa_actual==(int)pa.size())
        pa.push_back(p);
    else
        pa[pa_actual]=p;
}

void Fighter::setPbActual(Personaje* p)
{
    if(pb_actual==(int)pb.size())
        pb.push_back(p);
    else
        pb[pb_actual]=p;
}

void Fighter::mainLoop()
{
    for(;;)
    {
//        menu->pa.clear();
//        menu->pb.clear();
//
//        menu->loopMenu();
//        if(menu->getExitSignal())
//            break;
//
//        pa.clear();
//        pa.push_back(menu->pa[0]);
//        if(menu->pa.size()>=2)
//            pa.push_back(menu->pa[1]);
//        if(menu->pa.size()==3)
//            pa.push_back(menu->pa[2]);
//
//        pb.clear();
//        pb.push_back(menu->pb[0]);
//        if(menu->pb.size()>=2)
//            pb.push_back(menu->pb[1]);
//        if(menu->pb.size()==3)
//            pb.push_back(menu->pb[2]);
//
////        setPaActual(menu->pa[0]);
////        setPbActual(menu->pb[0]);
//        stage=menu->stage;
////        inputa=menu->inputa;
////        inputb=menu->inputb;
//        pos_stage=0;
//        //Juego
//        loopJuego();
    }
    //Drops
    sonido->drop();
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

    bool hay_colision=(
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

    if(hay_colision)
    {
        int x1,x2,y1,y2;
        if(x1a>x1r)x1=x1a;else x1=x1r;
        if(x2a<x2r)x2=x2a;else x2=x2r;

        if(y1a>y1r)y1=y1a;else y1=y1r;
        if(y2a<y2r)y2=y2a;else y2=y2r;

        px_colision=x1+((x2-x1)/2);
        py_colision=y1+((y2-y1)/2);
//        getPbActual()->setEntero("Colision.x",x1+((x2-x1)/2));
//        getPbActual()->setEntero("Colision.y",y1+((y2-y1)/2));
    }

    return hay_colision;
}

bool Fighter::getColisionHitBoxes(Personaje* atacante,stringw variable_atacante,Personaje* atacado,stringw variable_atacado,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
    vector <HitBox> hb_azules=atacado->getHitBoxes(variable_atacado);
    vector <HitBox> hb_rojas=atacante->getHitBoxes(variable_atacante);

    if(atacante->getString("orientation")=="i")
        for(int i=0; i<(int)hb_rojas.size(); i++)
        {
            int a=hb_rojas[i].p1x;
            int b=hb_rojas[i].p2x;
            hb_rojas[i].p1x=-b;
            hb_rojas[i].p2x=-a;
        }
    if(atacado->getString("orientation")=="i")
        for(int i=0; i<(int)hb_azules.size(); i++)
        {
            int a=hb_azules[i].p1x;
            int b=hb_azules[i].p2x;
            hb_azules[i].p1x=-b;
            hb_azules[i].p2x=-a;
        }


    int ax=atacado_x;
    int ay=-atacado_y;
    int rx=atacante_x;
    int ry=-atacante_y;

    for(int a=0; a<(int)hb_azules.size(); a++)
        for(int r=0; r<(int)hb_rojas.size(); r++)
            if(getColisionHitBoxes(hb_azules[a],hb_rojas[r],ax,ay,rx,ry))
                return true;
    return false;
}

bool Fighter::getColisionHitBoxes(Personaje *atacante,stringw variable_atacante,Personaje* atacado,stringw variable_atacado)
{
    vector <HitBox> hb_azules=atacado->getHitBoxes(variable_atacado);
    vector <HitBox> hb_rojas=atacante->getHitBoxes(variable_atacante);

    if(atacante->getString("orientation")=="i")
        for(int i=0; i<(int)hb_rojas.size(); i++)
        {
            int a=hb_rojas[i].p1x;
            int b=hb_rojas[i].p2x;
            hb_rojas[i].p1x=-b;
            hb_rojas[i].p2x=-a;
        }
    if(atacado->getString("orientation")=="i")
        for(int i=0; i<(int)hb_azules.size(); i++)
        {
            int a=hb_azules[i].p1x;
            int b=hb_azules[i].p2x;
            hb_azules[i].p1x=-b;
            hb_azules[i].p2x=-a;
        }


    int ax=atacado->getEntero("position_x");
    int ay=-atacado->getEntero("position_y");
    int rx=atacante->getEntero("position_x");
    int ry=-atacante->getEntero("position_y");

    for(int a=0; a<(int)hb_azules.size(); a++)
        for(int r=0; r<(int)hb_rojas.size(); r++)
            if(getColisionHitBoxes(hb_azules[a],hb_rojas[r],ax,ay,rx,ry))
                return true;
    return false;
}

void Fighter::logicaPersonaje(Personaje* p)
{
    //verificar distancia entre chars
    int distancia=p->getEntero("position_x")-p->personaje_contrario->getEntero("position_x");
    if(distancia<0)
        distancia=-distancia;
    p->setEntero("distance",distancia);
    //verificar si esta atacando
    if(p->getHitBoxes("red").size()>0)
    {
        p->setString("attacking","yes");
    }else
    {
        p->setString("attacking","no");
    }
    //verificar colision de hitboxes
    p->setString("hit","no");
    if(getColisionHitBoxes(p->personaje_contrario,"red",p,"blue") && p->personaje_contrario->getString("current_move")!="5")
    {
        p->setString("colision.red_hitboxes","yes");
        Movimiento* m=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
        if(!m->ya_pego)
        {
            p->setString("hit","yes");
            m->ya_pego=true;
            p->personaje_contrario->setEntero("Colision.x",px_colision);
            p->personaje_contrario->setEntero("Colision.y",py_colision);
        }
    }
    else
        p->setString("colision.red_hitboxes","no");

    if(getColisionHitBoxes(p->personaje_contrario,"blue",p,"blue"))
        p->setString("colision.blue_hitboxes","yes");
    else
        p->setString("colision.blue_hitboxes","no");

    //Change char
    if(stringw("on")==p->getString("change_char"))
    {
        if(p->numero==1)
        {
            int p_anterior=pa_actual;
            pa_actual++;
            if(pa_actual>=(int)pa.size())
                pa_actual=0;
            pa[pa_actual]->setEntero("position_x",pa[p_anterior]->getEntero("position_x"));
            pa[pa_actual]->setEntero("position_y",pa[p_anterior]->getEntero("position_y"));
            pa[pa_actual]->setString("orientation",pa[p_anterior]->getString("orientation"));
            p->setString("change_char","off");
            p=pa[pa_actual];
        }
        else
        {
            int p_anterior=pb_actual;
            pb_actual++;
            if(pb_actual>=(int)pb.size())
                pb_actual=0;
            pb[pb_actual]->setEntero("position_x",pb[p_anterior]->getEntero("position_x"));
            pb[pb_actual]->setEntero("position_y",pb[p_anterior]->getEntero("position_y"));
            pb[pb_actual]->setString("orientation",pb[p_anterior]->getString("orientation"));
            p->setString("change_char","off");
            p=pb[pb_actual];
            p->setString("change_char","off");
        }
        pa[pa_actual]->personaje_contrario=pb[pb_actual];
        pb[pb_actual]->personaje_contrario=pa[pa_actual];

        //aplicar movimiento entrance
        Movimiento* m=p->movimientos[p->getString("current_move")];
        m->frame_actual=0;
        m->tiempo_transcurrido=0;
        p->setString("current_move","entrance");
        p->setString("isActive.entrance","yes");
        sonido->reproducirSonido("entrance");
    }

    //verificar flip
    if(p->getEntero("position_x")>p->personaje_contrario->getEntero("position_x") && p->getString("current_move")=="5" && p->getString("state")=="standing")
        p->setString("orientation","i");
    if(p->getEntero("position_x")<p->personaje_contrario->getEntero("position_x") && p->getString("current_move")=="5" && p->getString("state")=="standing")
        p->setString("orientation","d");
    //get input
    stringw str_movimiento="5";
    if(pos_imagen_intro>=(int)match_intro.size())//si ya inicio la pelea
        str_movimiento=p->mapInputToMovimiento();

    //ejecutar cancel
    if(str_movimiento!="")
        if(p->cumpleCondiciones(str_movimiento))
        {
            Movimiento* m=p->movimientos[p->getString("current_move")];
            m->frame_actual=0;
            m->tiempo_transcurrido=0;
            m->ya_pego=false;
            p->setString("current_move",str_movimiento);
            sonido->reproducirSonido(str_movimiento);
            //setear isActive.
            p->setString(stringw("isActive.")+str_movimiento,"yes");
        }
    //Movimientos continuos
    //agregar nuevos
    for(int i=0; i<(int)p->inputs.size(); i++) //for each movimiento
        if(p->inputs[i].input[0]=="*")//buscar los constantes
            if(p->cumpleCondiciones(p->inputs[i].movimiento))//si cumple
            {
                bool existe=false;
                for(int j=0; j<(int)p->movimientos_constantes_actuales.size(); j++) //for each movimiento
                    if(p->movimientos_constantes_actuales[j]->nombre==p->inputs[i].movimiento)
                    {
                        existe=true;
                    }
                if(!existe)
                {
                    if(p->inputs[i].movimiento.subString(0,7)=="on_hit.")
                    {
                        if(p->getString("current_move").subString(0,7)=="on_hit.")
                        {
                            p->combo++;
                        }
                        Movimiento* m=p->movimientos[p->getString("current_move")];
                        Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
                        p->setEntero("hp.current_value",p->getEntero("hp.current_value")-m_contrario->damage);
                        m->frame_actual=0;
                        m->tiempo_transcurrido=0;
                        m->ya_pego=false;
                        p->setString("current_move",p->inputs[i].movimiento);
                        p->setString(stringw("isActive.")+p->inputs[i].movimiento,"yes");
                        sonido->reproducirSonido(str_movimiento);
                    }
                    else
                    {
                        stringw movimiento_temp=p->inputs[i].movimiento;
                        p->setString(stringw("isActive.")+movimiento_temp,"yes");
                        p->movimientos_constantes_actuales.push_back(p->movimientos[movimiento_temp]);
                    }
                }
            }

    //Agregar Proyectiles
    for(int i=0; i<(int)p->proyectiles_actuales.size(); i++)
    {
        Proyectil*proyectil=p->proyectiles_actuales[i];
        if(p->cumpleCondiciones(proyectil->frames[0].condiciones))//si cumple
        {
            p->setImagen(proyectil->imagen,proyectil->sprites[0]);
            p->setString(proyectil->estado,"on");
            p->setString(proyectil->orientacion,p->getString("orientation"));
            proyectil->frame_actual=0;
            proyectil->sprite_actual=0;
            proyectil->tiempo_transcurrido=0;
        }
    }
    p->logicaProyectiles();
}

void Fighter::aplicarModificadores(Personaje *p)
{
    //verificar q no se salgan de la pantalla
    int temp_pos_x=p->getEntero("position_x");
    int temp_pos_x_c=p->personaje_contrario->getEntero("position_x");

    //get movimiento y frame
    Movimiento* m=p->movimientos[p->getString("current_move")];
    Frame* f=&m->frames[m->frame_actual];
    //aplicar modificadores
    if(m->tiempo_transcurrido==0)
        p->aplicarModificadores(f->modificadores,p->getString("orientation")=="i");
    //avanzar frame
    if(m->tiempo_transcurrido==f->duracion)
    {
        m->frame_actual++;
        m->tiempo_transcurrido=0;
    }
    else
        m->tiempo_transcurrido++;
    //verificar fin de movimiento
    if(m->frame_actual==(int)m->frames.size())
    {
        m->ya_pego=false;
        if(p->getString("current_move").subString(0,7)=="on_hit.")
            p->combo=0;
        if(p->getString("current_move")!="ko")
        {
            m->frame_actual=0;
            p->setString(stringw("isActive.")+p->getString("current_move"),"no");
            p->setString("current_move","5");
        }else
        {
            m->frame_actual--;
        }
    }
    //verificar cancel de isActive.
    if(p->getString(stringw("isActive.")+p->getString("current_move"))=="no" && p->getString("current_move")!="5")
    {
            m->frame_actual=0;
            p->setString(stringw("isActive.")+p->getString("current_move"),"no");
            //poner idle
            p->setString("current_move","5");
    }
    //Movimientos continuos
    //ejecutar existentes
    for(int i=0; i<(int)p->movimientos_constantes_actuales.size(); i++)
    {
        Movimiento* mc=p->movimientos_constantes_actuales[i];
        if(p->getString(stringw("isActive.")+p->movimientos_constantes_actuales[i]->nombre)=="no")
        {
            mc->frame_actual=0;
            mc->ya_pego=false;
            p->movimientos_constantes_actuales.erase(p->movimientos_constantes_actuales.begin()+i);
            i--;
            continue;
        }
        Frame* fc=&mc->frames[mc->frame_actual];
        if(mc->tiempo_transcurrido==0)
            p->aplicarModificadores(fc->modificadores,p->getString("orientation")=="i");
        //avanzar frame
        if(mc->tiempo_transcurrido==fc->duracion)
        {
            mc->frame_actual++;
            mc->tiempo_transcurrido=0;
        }
        else
            mc->tiempo_transcurrido++;
        //verificar fin de movimiento
        if(mc->frame_actual==(int)mc->frames.size())
        {
            mc->frame_actual=0;
            mc->ya_pego=false;
            //pos_a_borrar.push_back(i);
            p->setString(stringw("isActive.")+p->movimientos_constantes_actuales[i]->nombre,"no");
            p->movimientos_constantes_actuales.erase(p->movimientos_constantes_actuales.begin()+i);
            i--;
        }
    }

    //logica de barras
    p->logicaBarras();

    //corregir si se sale x
    int distancia=p->getEntero("position_x")-p->personaje_contrario->getEntero("position_x");
    if(distancia>=1000 || distancia<=-1000 )
    {
        p->setEntero("position_x",temp_pos_x);
        p->personaje_contrario->setEntero("position_x",temp_pos_x_c);
    }

    //corregir si se sale y
    if(p->getEntero("position_y")<0)
    {
        p->setEntero("position_y",0);
    }
}

void Fighter::logicaStagePersonaje(Personaje* p)
{
    int borde_izq=0,borde_der=1024,desplazamiento;
    int sub_borde_izq=256,sub_borde_der=768;
    //int sub_borde_izq=256,sub_borde_der=1024;

    desplazamiento=sub_borde_izq-p->getEntero("position_x");
    if(desplazamiento>0
            && p->getEntero("position_x")<p->personaje_contrario->getEntero("position_x")
            && p->getEntero("position_x")>borde_izq-desplazamiento
            && p->personaje_contrario->getEntero("position_x")<borde_der-desplazamiento
            && pos_stage<stage->size/2-grafico->ventana_x/2)
    {
        p->personaje_contrario->setEntero("position_x",p->personaje_contrario->getEntero("position_x")+desplazamiento);
        p->setEntero("position_x",p->getEntero("position_x")+desplazamiento);
        //pos_stage+=desplazamiento;
        grafico->camera_x+=desplazamiento;
    }

    desplazamiento=p->getEntero("position_x")-sub_borde_der;
    if(desplazamiento>0
            && p->getEntero("position_x")>p->personaje_contrario->getEntero("position_x")
            && p->getEntero("position_x")<borde_der+desplazamiento
            && p->personaje_contrario->getEntero("position_x")>borde_izq+desplazamiento
            && pos_stage>-stage->size/2+grafico->ventana_x/2)
    {
        p->personaje_contrario->setEntero("position_x",p->personaje_contrario->getEntero("position_x")-desplazamiento);
        p->setEntero("position_x",p->getEntero("position_x")-desplazamiento);
        //pos_stage-=desplazamiento;
        grafico->camera_x-=desplazamiento;
    }

    if(p->getEntero("position_x")<borde_izq)
        p->setEntero("position_x",borde_izq+10);
    if(p->getEntero("position_x")>borde_der)
        p->setEntero("position_x",borde_der-10);

    if(p->personaje_contrario->getEntero("position_x")<borde_izq)
        p->personaje_contrario->setEntero("position_x",borde_izq+10);
    if(p->personaje_contrario->getEntero("position_x")>borde_der)
        p->personaje_contrario->setEntero("position_x",borde_der-10);
}

void Fighter::logicaStage()
{
    int pa_x=getPaActual()->getEntero("position_x");
    int pb_x=getPbActual()->getEntero("position_x");

    //verificar q los personajes no se salgan
    if(pa_x<-stage->size/2+grafico->ventana_x/2)//pa borde izquierdo
    {
        pa_x=-stage->size/2+grafico->ventana_x/2;
        getPaActual()->setEntero("position_x",pa_x);
    }
    if(pa_x>stage->size/2+grafico->ventana_x/2)//papa borde derecho
    {
        pa_x=stage->size/2+grafico->ventana_x/2;
        getPaActual()->setEntero("position_x",pa_x);
    }
    if(pb_x<-stage->size/2+grafico->ventana_x/2)//pb borde izquierdo
    {
        pb_x=-stage->size/2+grafico->ventana_x/2;
        getPbActual()->setEntero("position_x",pb_x);
    }
    if(pb_x>stage->size/2+grafico->ventana_x/2)//pb borde derecho
    {
        pb_x=stage->size/2+grafico->ventana_x/2;
        getPbActual()->setEntero("position_x",pb_x);
    }

    //get una nueva posicion de la stage
    int borde_izq=300;
    int borde_der=700;

    int pa_x_pantalla=pa_x+grafico->camera_x;
    int pa_y_pantalla=pb_x+grafico->camera_x;
    int nueva_pos=(pa_x+pb_x)/2-grafico->ventana_x/2;


    //verificar q  el stage no se salga
    if(nueva_pos>-stage->size/2+grafico->ventana_x/2
       && nueva_pos<stage->size/2-grafico->ventana_x/2
       )
    {
        grafico->camera_x=nueva_pos;
    }


    //Alineacion y
    int y_max=getPaActual()->getEntero("position_y");
    if(y_max<getPbActual()->getEntero("position_y"))
        y_max=getPbActual()->getEntero("position_y");

    grafico->camera_y=y_max/4;

//    if(pa_x<grafico->camera_x)
//        grafico->camera_x=pa_x;
//
//    if(pa_x>grafico->camera_x+grafico->ventana_x)
//        grafico->camera_x=pa_x-grafico->ventana_x;
//
//    if(pb_x<grafico->camera_x)
//        grafico->camera_x=pb_x;
//
//    if(pb_x>grafico->camera_x+grafico->ventana_x)
//        grafico->camera_x=pb_x-grafico->ventana_x;

//    if(pb_x<grafico->camera_x)
//        grafico->camera_x=-pb_x;

//    if(pa_x>grafico->camera_x+1024)
//        grafico->camera_x=-pa_x;

//    if(pb_x>grafico->camera_x+1024)
//        grafico->camera_x=-pb_x;
    //Validaciones de stage
    //logicaStagePersonaje(getPaActual());
    //logicaStagePersonaje(getPbActual());

//    if(pos_stage>stage->size/2-grafico->ventana_x/2)
//    {
//        int dif=pos_stage-(stage->size/2-grafico->ventana_x/2);
//        pos_stage=stage->size/2-grafico->ventana_x/2;
//        getPaActual()->setEntero("position_x",getPaActual()->getEntero("position_x")-dif);
//        getPbActual()->setEntero("position_x",getPbActual()->getEntero("position_x")-dif);
//    }
//    if(pos_stage<-stage->size/2+grafico->ventana_x/2)
//    {
//        int dif=pos_stage-(-stage->size/2+grafico->ventana_x/2);
//        pos_stage=-stage->size/2+grafico->ventana_x/2;
//        getPaActual()->setEntero("position_x",getPaActual()->getEntero("position_x")-dif);
//        getPbActual()->setEntero("position_x",getPbActual()->getEntero("position_x")-dif);
//    }
}


void Fighter::logica()
{
    logicaPersonaje(getPaActual());
    logicaPersonaje(getPbActual());
    aplicarModificadores(getPaActual());
    aplicarModificadores(getPbActual());
    logicaStage();
}

void Fighter::loopJuego()
{
    getPaActual()->comparacion_hp=getPaActual()->getEntero("hp.current_value");
    getPaActual()->comparacion_hp_contrario=getPbActual()->getEntero("hp.current_value");

    getPbActual()->comparacion_hp=getPbActual()->getEntero("hp.current_value");
    getPbActual()->comparacion_hp_contrario=getPbActual()->getEntero("hp.current_value");

    sonido->reproducirSonido("Stage.music");
    u32 anterior=grafico->device->getTimer()->getTime();
    for (;;)
    {
        //receiver->endEventProcess();
        grafico->device->run();
        //cout<<grafico->device->getTimer()->getTime()<<endl;
        //setear frames a "60"
        if(grafico->device->getTimer()->getTime()<anterior+16)
            continue;

        if(receiver->IsKeyPressed(irr::KEY_ESCAPE))///!!!
        {
            pause_menu->loopMenu();
            if(pause_menu->getExitSignal())
                break;
        }

        anterior=grafico->device->getTimer()->getTime();

        //logica
        logica();

        //render
        render();
        //receiver->startEventProcess();
    }
    sonido->pararSonido("Stage.music");
}

void itoa(int n, char *s, int b)
{
    static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    int i=0, sign;

    if ((sign = n) < 0)
        n = -n;

    do
    {
        s[i++] = digits[n % b];
    }
    while ((n /= b) > 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    //return strrev(s);
}

char *strrev(char *str)
{
    char *p1, *p2;

    if (!str || !*str)
        return str;

    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }

    return str;
}

void Fighter::dibujarBarra()
{
    irr::video::ITexture* texture_bar=grafico->getTexture("misc/bar.png");
    grafico->draw2DImage
    (   texture_bar,
        irr::core::dimension2d<irr::f32> (texture_bar->getOriginalSize ().Width,texture_bar->getOriginalSize ().Height),
        irr::core::rect<irr::f32>(0,0,texture_bar->getOriginalSize().Width,texture_bar->getOriginalSize().Height),
        irr::core::position2d<irr::f32>(grafico->ventana_x/2-texture_bar->getOriginalSize().Width/2,0),
        irr::core::position2d<irr::f32>(0,0),
        irr::f32(0), irr::core::vector2df (0,0),
        true,
        irr::video::SColor(255,255,255,255),
        false,
        false);
}

bool Fighter::render()
{
    if (grafico->isWindowActive())
    {
        grafico->beginScene();
        //Stage
        stage->dibujarBack(pos_stage);

        //Animaciones back
        getPaActual()->dibujarAnimacionesBack();
        getPbActual()->dibujarAnimacionesBack();
        //Personaje
        getPaActual()->dibujar();
        getPbActual()->dibujar();
        //Animaciones front
        getPaActual()->dibujarAnimacionesFront();
        getPbActual()->dibujarAnimacionesFront();

        //Hit Boxes
        if(receiver->IsKeyDownn(irr::KEY_KEY_H))
        {
            getPaActual()->dibujarHitBoxes("blue","",getPaActual()->getString("orientation")=="i",getPaActual()->getEntero("position_x"),getPaActual()->getEntero("position_y"));
            getPbActual()->dibujarHitBoxes("blue","",getPbActual()->getString("orientation")=="i",getPbActual()->getEntero("position_x"),getPbActual()->getEntero("position_y"));
            getPaActual()->dibujarHitBoxes("red","",getPaActual()->getString("orientation")=="i",getPaActual()->getEntero("position_x"),getPaActual()->getEntero("position_y"));
            getPbActual()->dibujarHitBoxes("red","",getPbActual()->getString("orientation")=="i",getPbActual()->getEntero("position_x"),getPbActual()->getEntero("position_y"));
        }

        if(receiver->IsKeyDownn(irr::KEY_KEY_2))
        {
            getPaActual()->rango++;
        }
        if(receiver->IsKeyDownn(irr::KEY_KEY_1))
        {
            getPaActual()->rango--;
        }


        getPaActual()->dibujarProyectiles();
        getPbActual()->dibujarProyectiles();

        //HP
        getPaActual()->dibujarBarras();
        getPbActual()->dibujarBarras();

        if(pa.size()>=2)
            get2doPa()->dibujarBarraPequena(get2doPa()->getBarra("hp"),50,100);
        if(pa.size()==3)
            get3erPa()->dibujarBarraPequena(get3erPa()->getBarra("hp"),50,150);

        if(pb.size()>=2)
            get2doPb()->dibujarBarraPequena(get2doPb()->getBarra("hp"),50,100);
        if(pb.size()==3)
            get3erPb()->dibujarBarraPequena(get3erPb()->getBarra("hp"),50,150);
//        pa->dibujarBarra("hp",312-70,50);
//        pb->dibujarBarra("hp",512+45,50);

        bool game_over_a=true;
        for(int i=0;i<(int)pa.size();i++)
            if(pa[i]->getEntero("hp.current_value")>0)
                game_over_a=false;

        bool game_over_b=true;
        for(int i=0;i<(int)pb.size();i++)
            if(pb[i]->getEntero("hp.current_value")>0)
                game_over_b=false;

        if(game_over_a && getPaActual()->getString("current_move")!="ko")
        {
            getPaActual()->setString("current_move","ko");
            getPaActual()->setString("isActive.ko","yes");
        }

        if(game_over_b && getPbActual()->getString("current_move")!="ko")
        {
            getPbActual()->setString("current_move","ko");
            getPbActual()->setString("isActive.ko","yes");
        }

        if(game_over_a || game_over_b)
        {
            //irr::video::ITexture* texture_gameover=grafico->getTexture("misc/ko/1.png");
            irr::video::ITexture* texture_gameover=ko[pos_imagen_ko].imagen;
            tiempo_actual_ko++;
            if(tiempo_actual_ko==duracion_ko)
            {
                pos_imagen_ko++;
                tiempo_actual_ko=0;
            }
            if(pos_imagen_ko>=(int)ko.size())
                pos_imagen_ko=0;
            int width=texture_gameover->getOriginalSize().Width;
            int height=texture_gameover->getOriginalSize().Height;
            grafico->draw2DImage
            (   texture_gameover,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,width,height),
                irr::core::position2d<irr::f32>((1024-width)/2,(grafico->ventana_y-height)/2),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (0,0),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }


        if(pos_imagen_intro<(int)match_intro.size() && pa[0]->getString("current_move")=="5" && pb[0]->getString("current_move")=="5")
        {
            //irr::video::ITexture* texture_gameover=grafico->getTexture("misc/ko/1.png");
            irr::video::ITexture* texture_gameover=match_intro[pos_imagen_intro].imagen;
            tiempo_actual_intro++;
            if(tiempo_actual_intro==duracion_intro)
            {
                pos_imagen_intro++;
                tiempo_actual_intro=0;
            }
            //if(pos_imagen_intro>=(int)ko.size())
            //    pos_imagen_intro=0;
            int width=texture_gameover->getOriginalSize().Width;
            int height=texture_gameover->getOriginalSize().Height;
            grafico->draw2DImage
            (   texture_gameover,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,width,height),
                irr::core::position2d<irr::f32>((1024-width)/2,(grafico->ventana_y-height)/2),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (0,0),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }


        if(getPaActual()->getEntero("hp.current_value")<=0 && !(game_over_a || game_over_b))
        {
            getPaActual()->setString("change_char","on");
        }
        if(getPbActual()->getEntero("hp.current_value")<=0 && !(game_over_a || game_over_b))
        {
            getPbActual()->setString("change_char","on");
        }
        stage->dibujarFront(pos_stage);

        dibujarBarra();

        if(pa[pa_actual]->combo>0)
            grafico->drawText(stringw(pa[pa_actual]->combo+1)+" hits",core::rect<s32>(50,100,0,0),video::SColor (255,255,255,255));
        if(pb[pb_actual]->combo>0)
            grafico->drawText(stringw(pb[pb_actual]->combo+1)+" hits",core::rect<s32>(900,100,0,0),video::SColor (255,255,255,255));
//
//
        //Movimento actual
        //grafico->drawText(pa->getString("current_move"),irr::core::rect<irr::s32>(50,50,500,500),irr::video::ECP_GREEN);

//        stringw str=pb->getString("current_move")+","+pb->getString("estado_posicion")+": ";
//        for(int i=0;i<(int)pb->input->getBufferInputs().size();i++)
//            str+=pb->input->getBufferInputs()[i]+"-";
//        grafico->device->setWindowCaption(str.c_str());
//        grafico->device->setWindowCaption(pb->getString("colision.red_hitboxes").c_str());
//	int num = pa->getEntero("position_y");
//	char buf[5];

//	 convert 123 to string [buf]
//	itoa(num, buf, 10);
//	stringw str(strrev(buf));
//grafico->device->setWindowCaption(str.c_str());
//        grafico->device->setWindowCaption((pa->getEntero("position_x")+","+pa->getEntero("position_y")).c_str());

//
//        //grafico->draw2DRectangle(SColor(1000,0,100,0),core::rect<s32>(pa->getEntero("position_x"),pa->getEntero("position_y"),pa->getEntero("position_x")+100,pa->getEntero("position_y")+100));
//
//        int dimension_x=50;
//        int dimension_y=50;
//        grafico->draw2DImage
//    (   grafico->getTexture("resources/green.png"),
//        irr::core::dimension2d<irr::f32> (dimension_x,dimension_y),
//        irr::core::rect<irr::f32>(0,0,dimension_x,dimension_y),
//        irr::core::position2d<irr::f32>(pa->getEntero("position_x"),pa->getEntero("position_y")),
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

void Fighter::escribirInputsXML()
{
    TiXmlDocument *doc=new TiXmlDocument();
    inputb->getXML(inputa->getXML(doc));
    doc->SaveFile( "misc/inputs.xml" );
}
