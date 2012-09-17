#include "../include/Fighter.h"
Fighter::Fighter(Sonido* sonido,Grafico* grafico,Receiver* receiver,vector<Personaje*>pa,vector<Personaje*>pb,Stage*stage,int victories_a,int victories_b)
{
    this->victories_a=victories_a;
    this->victories_b=victories_b;
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

    for(int i=0; i<(int)pa.size(); i++)
        pa[i]->stage_piso=stage->pos_piso;
    for(int i=0; i<(int)pb.size(); i++)
        pb[i]->stage_piso=stage->pos_piso;

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

    //menu=new Menu(grafico,receiver,sonido,(char*)"menu/main_menu.xml");
    pause_menu=new Menu(grafico,receiver,sonido,(char*)"menu/pause_menu.xml");

    pos_stage=0;
    this->pa=pa;
    this->pb=pb;
    pa_vivos=(int)pa.size();
    pb_vivos=(int)pb.size();
    this->stage=stage;
    //Juego
    getPaActual()->setString("current_move","intro");
    getPbActual()->setString("current_move","intro");
    getPaActual()->setString("isActive.intro","yes");
    getPbActual()->setString("isActive.intro","yes");
    getPaActual()->setString("orientation","d");
    getPbActual()->setString("orientation","i");
    loopJuego();
}

Fighter::~Fighter()
{
    for(int i=0;i<(int)pa.size();i++)
        delete pa[i];
    for(int i=0;i<(int)pb.size();i++)
        delete pb[i];
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
        if(x1a>x1r)x1=x1a;
        else x1=x1r;
        if(x2a<x2r)x2=x2a;
        else x2=x2r;

        if(y1a>y1r)y1=y1a;
        else y1=y1r;
        if(y2a<y2r)y2=y2a;
        else y2=y2r;

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
    p->setEntero("distance",distancia);
    if(distancia<0)
        distancia=-distancia;
    p->setEntero("distance_absolute",distancia);
    //verificar colision de hitboxes
    p->setString("hit","no");
    if(getColisionHitBoxes(p->personaje_contrario,"red",p,"blue") && p->personaje_contrario->getString("current_move")!="5")
    {
        p->setString("colision.red_hitboxes","yes");
        Movimiento* m=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
        if(!m->ya_pego || m->multihit)
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
    if(p->numero==1 && pa_vivos<1)
        p->setString("change_char","off");
    if(p->numero==2 && pb_vivos<1)
        p->setString("change_char","off");
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
        sonido->reproducirSonido(p->char_name+"entrance");
    }

    //verificar flip
    if(p->getEntero("position_x")>p->personaje_contrario->getEntero("position_x")
            && (p->getString("current_move")=="5" || p->getString("current_move")=="2")
            && (p->getString("state")=="standing" || p->getString("state")=="crouch"))
        p->setString("orientation","i");

    if(p->getEntero("position_x")<p->personaje_contrario->getEntero("position_x")
            && (p->getString("current_move")=="5" || p->getString("current_move")=="2")
            && (p->getString("state")=="standing" || p->getString("state")=="crouch"))
        p->setString("orientation","d");
    //get input
    stringw str_movimiento="";
    if(pos_imagen_intro>=(int)match_intro.size())//si ya inicio la pelea
        str_movimiento=p->mapInputToMovimiento();
    if(game_over_a||game_over_b)
        str_movimiento="5";

    //ejecutar cancel
    if(str_movimiento!="")
        if(p->cumpleCondiciones(str_movimiento))
        {
            if((str_movimiento=="change_char"//validacion de no poder hacer "change_char" si no hay mas chars
                    && ((p->numero==1&&pa_vivos<=1)||(p->numero==2&&pb_vivos<=1)))
                    ==false)
            {
                if(p->numero==1)
                    move_cancel_pa=str_movimiento;
                if(p->numero==2)
                    move_cancel_pb=str_movimiento;

//                Movimiento* m=p->movimientos[p->getString("current_move")];
//                m->frame_actual=0;
//                m->tiempo_transcurrido=0;
//                m->ya_pego=false;
//                p->setString("current_move",str_movimiento);
//                sonido->reproducirSonido(p->char_name+str_movimiento);
//                //setear isActive.
//                p->setString(stringw("isActive.")+str_movimiento,"yes");
            }
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
                        if(p->numero==1)
                        {
                            hit_cancel_pa=p->inputs[i].movimiento;
                            Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
                            hit_cancel_pa_damage=m_contrario->damage;
                        }
                        if(p->numero==2)
                        {
                            hit_cancel_pb=p->inputs[i].movimiento;
                            Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
                            hit_cancel_pb_damage=m_contrario->damage;
                        }
//                        if(p->getString("current_move").subString(0,7)=="on_hit.")
//                        {
//                            p->combo++;
//                        }
//                        Movimiento* m=p->movimientos[p->getString("current_move")];
//                        Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
//                        p->setEntero("hp.current_value",p->getEntero("hp.current_value")-m_contrario->damage);
//                        m->frame_actual=0;
//                        m->tiempo_transcurrido=0;
//                        m->ya_pego=false;
//                        p->setString("current_move",p->inputs[i].movimiento);
//                        p->setString(stringw("isActive.")+p->inputs[i].movimiento,"yes");
//                        sonido->reproducirSonido(p->char_name+p->getString("current_move"));
                    }
                    else
                    {
                        stringw movimiento_temp=p->inputs[i].movimiento;
                        p->setString(stringw("isActive.")+movimiento_temp,"yes");
                        p->movimientos_constantes_actuales.push_back(p->movimientos[movimiento_temp]);
                    }
                }
            }
}

void Fighter::logica()
{
    //logica proyectiles
    getPaActual()->logicaProyectiles();
    getPbActual()->logicaProyectiles();
    //verificar si estan atacando
    if(getPaActual()->getHitBoxes("red").size()>0
       || getPaActual()->proyectiles_activos>0)
    {
        getPaActual()->setString("attacking","yes");
    }
    else
    {
        getPaActual()->setString("attacking","no");
    }
    if(getPbActual()->getHitBoxes("red").size()>0
       || getPbActual()->proyectiles_activos>0)
    {
        getPbActual()->setString("attacking","yes");
    }
    else
    {
        getPbActual()->setString("attacking","no");
    }

    move_cancel_pa="";
    move_cancel_pb="";

    hit_cancel_pa="";
    hit_cancel_pa_damage=0;
    hit_cancel_pb="";
    hit_cancel_pb_damage=0;

    //LOGICAS PERSONAJE
    logicaPersonaje(getPaActual());
    logicaPersonaje(getPbActual());


    //cancelar justamente
    if(move_cancel_pa!="")
    {

        Personaje* p=getPaActual();
                Movimiento* m=p->movimientos[p->getString("current_move")];
                m->frame_actual=0;
                m->tiempo_transcurrido=0;
                m->ya_pego=false;
                p->setString("current_move",move_cancel_pa);
                sonido->reproducirSonido(p->char_name+move_cancel_pa);
                //setear isActive.
                p->setString(stringw("isActive.")+move_cancel_pa,"yes");
    }

    if(move_cancel_pb!="")
    {
        Personaje* p=getPbActual();
                Movimiento* m=p->movimientos[p->getString("current_move")];
                m->frame_actual=0;
                m->tiempo_transcurrido=0;
                m->ya_pego=false;
                p->setString("current_move",move_cancel_pb);
                sonido->reproducirSonido(p->char_name+move_cancel_pb);
                //setear isActive.
                p->setString(stringw("isActive.")+move_cancel_pb,"yes");
    }

    if(hit_cancel_pa!="")
    {
        Personaje*p=getPaActual();
            if(p->getString("current_move").subString(0,7)=="on_hit.")
            {
                p->combo++;
            }
            Movimiento* m=p->movimientos[p->getString("current_move")];
            Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
            p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_damage);
            m->frame_actual=0;
            m->tiempo_transcurrido=0;
            m->ya_pego=false;
            p->setString("current_move",hit_cancel_pa);
            p->setString(stringw("isActive.")+hit_cancel_pa,"yes");
            sonido->reproducirSonido(p->char_name+p->getString("current_move"));
    }

    if(hit_cancel_pb!="")
    {
        Personaje*p=getPbActual();
            if(p->getString("current_move").subString(0,7)=="on_hit.")
            {
                p->combo++;
            }
            Movimiento* m=p->movimientos[p->getString("current_move")];
            Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
            p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pb_damage);
            m->frame_actual=0;
            m->tiempo_transcurrido=0;
            m->ya_pego=false;
            p->setString("current_move",hit_cancel_pb);
            p->setString(stringw("isActive.")+hit_cancel_pb,"yes");
            sonido->reproducirSonido(p->char_name+p->getString("current_move"));
    }


    //aplicar efectos proyectiles
    getPaActual()->aplicarEfectosProyectiles();
    getPbActual()->aplicarEfectosProyectiles();
    //APLICAR MODIFICADORES
    aplicarModificadores(getPaActual());
    aplicarModificadores(getPbActual());
    logicaStage();
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
        }
        else
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
    int dist_max=grafico->ventana_x-100;
    if(distancia>=dist_max|| distancia<=-dist_max)
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

void Fighter::logicaStage()
{
    int pa_x=getPaActual()->getEntero("position_x");
    int pb_x=getPbActual()->getEntero("position_x");
    int marco_x=50;

    //verificar q los personajes no se salgan
    if(pa_x<-stage->size/2+grafico->ventana_x/2+marco_x)//pa borde izquierdo
    {
        pa_x=-stage->size/2+grafico->ventana_x/2+marco_x;
        getPaActual()->setEntero("position_x",pa_x);
    }
    if(pa_x>stage->size/2+grafico->ventana_x/2-marco_x)//pa borde derecho
    {
        pa_x=stage->size/2+grafico->ventana_x/2-marco_x;
        getPaActual()->setEntero("position_x",pa_x);
    }
    if(pb_x<-stage->size/2+grafico->ventana_x/2+marco_x)//pb borde izquierdo
    {
        pb_x=-stage->size/2+grafico->ventana_x/2+marco_x;
        getPbActual()->setEntero("position_x",pb_x);
    }
    if(pb_x>stage->size/2+grafico->ventana_x/2-marco_x)//pb borde derecho
    {
        pb_x=stage->size/2+grafico->ventana_x/2-marco_x;
        getPbActual()->setEntero("position_x",pb_x);
    }

    //get una nueva posicion de la stage
    int borde_izq=500;
    int borde_der=900;

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
        //Salir con cualquier boton si ya termino la pelea
        if(game_over_a || game_over_b)
        {
            stringw last_input=getPaActual()->input->getBufferInputs()[0];
            if(last_input!="1"
               && last_input!="2"
               && last_input!="3"
               && last_input!="4"
               && last_input!="5"
               && last_input!="6"
               && last_input!="7"
               && last_input!="8"
               && last_input!="9"
               && (getPaActual()->getString("current_move")=="5"||getPbActual()->getString("current_move")=="5")
                    ||getPaActual()->getString("current_move")=="ko"&&getPbActual()->getString("current_move")=="ko")
                break;
        }
        //receiver->endEventProcess();
        grafico->device->run();
        //cout<<grafico->device->getTimer()->getTime()<<endl;
        //setear frames a "60"
        if(grafico->device->getTimer()->getTime()<anterior+16)
            continue;

        if(receiver->IsKeyDownn(irr::KEY_ESCAPE))///!!!
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

    for(int i=0;i<victories_a;i++)
    {
        irr::video::ITexture* texture_victory=grafico->getTexture("misc/victory.png");
        int offset_x=100;
        int offset_y=175;
        int separation_x=texture_victory->getOriginalSize().Width;
        grafico->draw2DImage
        (   texture_victory,
            irr::core::dimension2d<irr::f32> (texture_victory->getOriginalSize ().Width,texture_victory->getOriginalSize ().Height),
            irr::core::rect<irr::f32>(0,0,texture_victory->getOriginalSize().Width,texture_victory->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(grafico->ventana_x/2-texture_victory->getOriginalSize().Width/2-offset_x-i*separation_x,offset_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0,0),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }

    for(int i=0;i<victories_b;i++)
    {
        irr::video::ITexture* texture_victory=grafico->getTexture("misc/victory.png");
        int offset_x=100;
        int offset_y=175;
        int separation_x=texture_victory->getOriginalSize().Width;
        grafico->draw2DImage
        (   texture_victory,
            irr::core::dimension2d<irr::f32> (texture_victory->getOriginalSize ().Width,texture_victory->getOriginalSize ().Height),
            irr::core::rect<irr::f32>(0,0,texture_victory->getOriginalSize().Width,texture_victory->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(grafico->ventana_x/2-texture_victory->getOriginalSize().Width/2+offset_x+i*separation_x,offset_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0,0),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
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

        pa_vivos=0;
        for(int i=0; i<(int)pa.size(); i++)
            if(pa[i]->getEntero("hp.current_value")>0)
                pa_vivos++;

        pb_vivos=0;
        for(int i=0; i<(int)pb.size(); i++)
            if(pb[i]->getEntero("hp.current_value")>0)
                pb_vivos++;

        game_over_a=pa_vivos<=0;
        game_over_b=pb_vivos<=0;

        if(game_over_a && getPaActual()->getString("current_move")!="ko")
        {
            //cancelar anterior
            Personaje*p=getPaActual();
            Movimiento* m=p->movimientos[p->getString("current_move")];
            m->frame_actual=0;
            m->tiempo_transcurrido=0;
            m->ya_pego=false;

            p=getPbActual();
            m=p->movimientos[p->getString("current_move")];
            m->frame_actual=0;
            m->tiempo_transcurrido=0;
            m->ya_pego=false;
            //Agregar nuevo
            getPaActual()->setString("current_move","ko");
            getPaActual()->setString("isActive.ko","yes");

            if(!game_over_b)
            {
                getPbActual()->setString("current_move","victory");
                getPbActual()->setString("isActive.victory","yes");
            }
        }

        if(game_over_b && getPbActual()->getString("current_move")!="ko")
        {
            //cancelar anterior
            Personaje*p=getPaActual();
            Movimiento* m=p->movimientos[p->getString("current_move")];
            m->frame_actual=0;
            m->tiempo_transcurrido=0;
            m->ya_pego=false;

            p=getPbActual();
            m=p->movimientos[p->getString("current_move")];
            m->frame_actual=0;
            m->tiempo_transcurrido=0;
            m->ya_pego=false;
            //Agregar nuevo
            getPbActual()->setString("current_move","ko");
            getPbActual()->setString("isActive.ko","yes");

            if(!game_over_a)
            {
                getPaActual()->setString("current_move","victory");
                getPaActual()->setString("isActive.victory","yes");
            }
        }

        if(game_over_a || game_over_b)
        {
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
                irr::core::position2d<irr::f32>((grafico->ventana_x-width)/2,(grafico->ventana_y-height)/2),
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
                irr::core::position2d<irr::f32>((grafico->ventana_x-width)/2,(grafico->ventana_y-height)/2),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (0,0),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }


        if(getPaActual()->getEntero("hp.current_value")<=0
           && !(game_over_a || game_over_b)
           && getPaActual()->getString("current_move")!="change_char"
           )
        {
            getPaActual()->setString("current_move","change_char");
            getPaActual()->setString("isActive.change_char","yes");
        }
        if(getPbActual()->getEntero("hp.current_value")<=0
           && !(game_over_a || game_over_b)
           && getPbActual()->getString("current_move")!="change_char"
           )
        {
            getPbActual()->setString("current_move","change_char");
            getPbActual()->setString("isActive.change_char","yes");
        }
        stage->dibujarFront(pos_stage);

        dibujarBarra();

        if(pa[pa_actual]->combo>0)
            grafico->drawText(stringw(pa[pa_actual]->combo+1)+" hits",core::rect<s32>(50,200,0,0),video::SColor (255,255,255,255));
        if(pb[pb_actual]->combo>0)
            grafico->drawText(stringw(pb[pb_actual]->combo+1)+" hits",core::rect<s32>(grafico->ventana_x-300,200,0,0),video::SColor (255,255,255,255));

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
