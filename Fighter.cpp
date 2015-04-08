#include "Fighter.h"
Fighter::Fighter(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,vector<Personaje*>pa,vector<Personaje*>pb,Stage*stage,int victories_a,int victories_b,bool is_training)
{
    writeLogLine("Initializing Fighter game");

    this->victories_a=victories_a;
    this->victories_b=victories_b;

    this->is_training = is_training;

    this->stop_time_pa=false;
    this->stop_time_pb=false;

    string configxml_path=assets_directory+"config.xml";
    TiXmlDocument doc_t(configxml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlElement* elem_victory=doc->FirstChild("VictoryIcon")->ToElement();
    victory_image_x=atoi(elem_victory->Attribute("x"));
    victory_image_y=atoi(elem_victory->Attribute("y"));

    TiXmlElement* elem_intro=doc->FirstChild("IntroAnimation")->ToElement();
    int intro_frames=atoi(elem_intro->Attribute("frames"));
    duracion_intro=atoi(elem_intro->Attribute("duration"));

    TiXmlElement* elem_ko=doc->FirstChild("KOAnimation")->ToElement();
    int ko_frames=atoi(elem_ko->Attribute("frames"));
    duracion_ko=atoi(elem_ko->Attribute("duration"));

    texture_bar=painter->getTexture(assets_directory+"misc/bar.png");
    texture_victory=painter->getTexture(assets_directory+"misc/victory.png");

    tiempo_actual_intro=0;
    pos_imagen_intro=0;
    for(int i=0;i<intro_frames;i++)
    {
        match_intro.push_back(new Imagen(painter->getTexture(assets_directory+"misc/match_intro/"+toString(i+1)+".png"),1,0,0));
    }

    tiempo_actual_ko=0;
    pos_imagen_ko=0;
    for(int i=0;i<ko_frames;i++)
    {
        ko.push_back(new Imagen(painter->getTexture(assets_directory+"misc/ko/"+toString(i+1)+".png"),1,0,0));
    }

    writeLogLine("Loading stage misc.");

    for(int i=0; i<(int)pa.size(); i++)
        pa[i]->stage_piso=stage->pos_piso;
    for(int i=0; i<(int)pb.size(); i++)
        pb[i]->stage_piso=stage->pos_piso;
    //Engines
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    //stage=new Stage(grafico,sonido);

    //stage->loadFromXML((char*)"Stage1");
    //this->stage=(Stage*)new StageXml(grafico,(char*)"stages/Stage1/Stage1.xml");
    this->pa_actual=0;
    this->pb_actual=0;

    writeLogLine("Initializing pause menu.");
    pause_menu=new Menu(painter,receiver,sonido,assets_directory+"menu/pause_menu.svg");

    writeLogLine("Setting player misc.");

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
    getPaActual()->flipRight();
    getPbActual()->flipLeft();
    //Set chars inital position
    getPaActual()->setEntero("position_x",painter->screen_width/2-250);
    getPbActual()->setEntero("position_x",painter->screen_width/2+250);

    input_buffer_images['1']=painter->getTexture(assets_directory+"misc/input_buffer/1.png");
    input_buffer_images['2']=painter->getTexture(assets_directory+"misc/input_buffer/2.png");
    input_buffer_images['3']=painter->getTexture(assets_directory+"misc/input_buffer/3.png");
    input_buffer_images['4']=painter->getTexture(assets_directory+"misc/input_buffer/4.png");
    input_buffer_images['5']=painter->getTexture(assets_directory+"misc/input_buffer/5.png");
    input_buffer_images['6']=painter->getTexture(assets_directory+"misc/input_buffer/6.png");
    input_buffer_images['7']=painter->getTexture(assets_directory+"misc/input_buffer/7.png");
    input_buffer_images['8']=painter->getTexture(assets_directory+"misc/input_buffer/8.png");
    input_buffer_images['9']=painter->getTexture(assets_directory+"misc/input_buffer/9.png");

    input_buffer_images['a']=painter->getTexture(assets_directory+"misc/input_buffer/a.png");
    input_buffer_images['b']=painter->getTexture(assets_directory+"misc/input_buffer/b.png");
    input_buffer_images['c']=painter->getTexture(assets_directory+"misc/input_buffer/c.png");
    input_buffer_images['d']=painter->getTexture(assets_directory+"misc/input_buffer/d.png");
    input_buffer_images['e']=painter->getTexture(assets_directory+"misc/input_buffer/e.png");
    input_buffer_images['f']=painter->getTexture(assets_directory+"misc/input_buffer/f.png");

    hitboxes_are_visible=false;
    buffer_is_visible=false;

    counter_pa_visible_frame=0;
    counter_pb_visible_frame=0;
    training_health_regen_frame=0;

    loopJuego();
}

Fighter::~Fighter()
{
    writeLogLine("Deleting game.");
    for(int i=0;i<(int)pa.size();i++)
        delete pa[i];
    for(int i=0;i<(int)pb.size();i++)
        delete pb[i];
    delete stage;

    for(;!ko.empty();)
    {
        Imagen*imagen=ko.back();
        ko.pop_back();
        delete imagen;
    }

    for(;!match_intro.empty();)
    {
        Imagen*imagen=match_intro.back();
        match_intro.pop_back();
        delete imagen;
    }

    for(map<char,Image*>::iterator i=input_buffer_images.begin();
        i!=input_buffer_images.end();
        i++)
        delete (*i).second;

    delete texture_bar;
    delete texture_victory;
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

bool Fighter::getColisionHitBoxes(HitBox* hb_azul,HitBox* hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y)
{
    int x1r=hb_roja->p1x+atacante_x;
    int y1r=hb_roja->p1y+atacante_y;
    int x2r=hb_roja->p2x+atacante_x;
    int y2r=hb_roja->p2y+atacante_y;

    int x1a=hb_azul->p1x+atacado_x;
    int y1a=hb_azul->p1y+atacado_y;
    int x2a=hb_azul->p2x+atacado_x;
    int y2a=hb_azul->p2y+atacado_y;

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

bool Fighter::getColisionHitBoxes(Personaje *atacante,std::string variable_atacante,Personaje* atacado,std::string variable_atacado)
{
    std::vector <HitBox*> hb_azules=atacado->getHitBoxes(variable_atacado);
    std::vector <HitBox*> hb_rojas=atacante->getHitBoxes(variable_atacante);

    if(atacante->getString("orientation")=="i")
        for(int i=0; i<(int)hb_rojas.size(); i++)
        {
            int a=hb_rojas[i]->p1x;
            int b=hb_rojas[i]->p2x;
            hb_rojas[i]->p1x=-b;
            hb_rojas[i]->p2x=-a;
        }
    if(atacado->getString("orientation")=="i")
        for(int i=0; i<(int)hb_azules.size(); i++)
        {
            int a=hb_azules[i]->p1x;
            int b=hb_azules[i]->p2x;
            hb_azules[i]->p1x=-b;
            hb_azules[i]->p2x=-a;
        }


    int ax=atacado->getEntero("position_x");
    int ay=-atacado->getEntero("position_y");
    int rx=atacante->getEntero("position_x");
    int ry=-atacante->getEntero("position_y");

    for(int a=0; a<(int)hb_azules.size(); a++)
        for(int r=0; r<(int)hb_rojas.size(); r++)
            if(getColisionHitBoxes(hb_azules[a],hb_rojas[r],ax,ay,rx,ry))
            {
                if(atacante->getString("orientation")=="i")
                    for(int i=0; i<(int)hb_rojas.size(); i++)
                    {
                        int a=hb_rojas[i]->p1x;
                        int b=hb_rojas[i]->p2x;
                        hb_rojas[i]->p1x=-b;
                        hb_rojas[i]->p2x=-a;
                    }
                if(atacado->getString("orientation")=="i")
                    for(int i=0; i<(int)hb_azules.size(); i++)
                    {
                        int a=hb_azules[i]->p1x;
                        int b=hb_azules[i]->p2x;
                        hb_azules[i]->p1x=-b;
                        hb_azules[i]->p2x=-a;
                    }
                return true;
            }

    if(atacante->getString("orientation")=="i")
        for(int i=0; i<(int)hb_rojas.size(); i++)
        {
            int a=hb_rojas[i]->p1x;
            int b=hb_rojas[i]->p2x;
            hb_rojas[i]->p1x=-b;
            hb_rojas[i]->p2x=-a;
        }
    if(atacado->getString("orientation")=="i")
        for(int i=0; i<(int)hb_azules.size(); i++)
        {
            int a=hb_azules[i]->p1x;
            int b=hb_azules[i]->p2x;
            hb_azules[i]->p1x=-b;
            hb_azules[i]->p2x=-a;
        }
    return false;
}

void Fighter::cancel(Personaje *p)
{
    RosalilaInputs*input=getPaActual()->input;
    if(p->numero==2)
        input=getPbActual()->input;

    Movimiento* m=p->movimientos[p->getString("current_move")];
    m->frame_actual=0;
    m->tiempo_transcurrido=0;
    m->ya_pego=false;
    p->setString(std::string("isActive.")+p->getString("current_move"),"no");
    if(p->getEntero("position_y")>0)
    {
        p->setString("current_move","idle.jump");
        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        m_nuevo->frame_actual=0;
        m_nuevo->tiempo_transcurrido=0;
        m_nuevo->ya_pego=true;
        velocityInheritance(p,m,m_nuevo);
    }
    else if(m->crouched
            &&
            (input->getBufferRosalilaInputs()[0][0]=='1' || input->getBufferRosalilaInputs()[0][0]=='2' || input->getBufferRosalilaInputs()[0][0]=='3')
            )
    {
        p->setString("current_move","idle.crouch");
        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        m_nuevo->frame_actual=m_nuevo->repeat_from;
        m_nuevo->tiempo_transcurrido=0;
        velocityInheritance(p,m,m_nuevo);
    }
    else if(p->getEntero("position_y")<=0 && m->land_cancelable)
    {
        p->setString("current_move","idle.land_cancel");
        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        m_nuevo->frame_actual=0;
        m_nuevo->tiempo_transcurrido=0;
        velocityInheritance(p,m,m_nuevo);

        if(p->getEntero("position_x")>p->personaje_contrario->getEntero("position_x"))
            p->flipLeft();
        else
            p->flipRight();

    }else
    {
        p->setString("current_move","idle.stand");
        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        m_nuevo->frame_actual=0;
        m_nuevo->tiempo_transcurrido=0;
        velocityInheritance(p,m,m_nuevo);
    }

    Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
    //aplicar modificadores de la primera frame
    Frame* f=m_nuevo->frames[m_nuevo->frame_actual];
    if(m_nuevo->tiempo_transcurrido==0)
        p->aplicarModificadores(f->modificadores,p->getString("orientation")=="i");
}

void Fighter::landCancel(Personaje *p)
{
    Movimiento* m=p->movimientos[p->getString("current_move")];
    if(p->getEntero("position_y")<=0 && m->land_cancelable)
    {
        cancel(p);
    }
}

void Fighter::colisionCheck(Personaje*p)
{
    p->setString("hit","no");
    if(getColisionHitBoxes(p,"red",p->personaje_contrario,"blue") && p->personaje_contrario->getString("current_move")!="idle.stand")
    {
        p->setString("colision.red_to_blue","yes");
    }
    else
        p->setString("colision.red_to_blue","no");

    if(getColisionHitBoxes(p,"red",p->personaje_contrario,"red"))
    {
        p->setString("colision.red_to_red","yes");
    }
    else
    {
        p->setString("colision.red_to_red","no");
    }

    if(getColisionHitBoxes(p,"blue",p->personaje_contrario,"blue"))
        p->setString("colision.blue_to_blue","yes");
    else
        p->setString("colision.blue_to_blue","no");

    if(getColisionHitBoxes(p,"blue",p->personaje_contrario,"red"))
    {
        p->setString("colision.blue_to_red","yes");
        Movimiento* m=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
        if(!m->ya_pego || m->multihit)
        {
            p->setString("hit","yes");
            painter->explode(px_colision,py_colision+painter->screen_height);
            m->ya_pego=true;
            p->personaje_contrario->setEntero("Colision.x",px_colision);
            p->personaje_contrario->setEntero("Colision.y",py_colision);

            if(m->cancel_on_hit!="")
            {
                if(p->personaje_contrario->numero==1)
                    move_cancel_pa=m->cancel_on_hit;
                if(p->personaje_contrario->numero==2)
                    move_cancel_pb=m->cancel_on_hit;
            }
        }
    }
    else
        p->setString("colision.blue_to_red","no");
}

void Fighter::logicaPersonaje(Personaje* p)
{
    landCancel(p);
    //verificar distancia entre chars
    int distancia=p->getEntero("position_x")-p->personaje_contrario->getEntero("position_x");
    p->setEntero("distance",distancia);
    if(distancia<0)
        distancia=-distancia;
    p->setEntero("distance_absolute",distancia);

    colisionCheck(p);

    //Change char
    if(p->numero==1 && pa_vivos<1)
        p->setString("change_char","off");
    if(p->numero==2 && pb_vivos<1)
        p->setString("change_char","off");
    if(std::string("on")==p->getString("change_char"))
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
        m->ya_pego=false;
        p->setString("current_move","entrance");
        p->setString("isActive.entrance","yes");
        sonido->playSound(p->char_name+"entrance");
    }

    //get input
    std::string str_movimiento="";
    if(pos_imagen_intro>=(int)match_intro.size())//si ya inicio la pelea
        str_movimiento=p->mapInputToMovimiento();
    if(game_over_a||game_over_b)
        str_movimiento="idle.stand";

    //ejecutar cancel
    if(str_movimiento!="")
    {
        if(str_movimiento.substr(0,7)=="on_hit."
                && p->getString("current_move")=="on_hit.air_knockdown")
            applyCameraEffect();
        if(p->getString("current_move").substr(0,7)!="on_hit."
            && p->getString("current_move").substr(0,4)!="walk"
            && p->getString("current_move").substr(0,5)!="idle."
            && str_movimiento.substr(0,7)=="on_hit.")
        {
            if(p->numero==1)
                counter_pa_visible_frame=45;
            else
                counter_pb_visible_frame=45;
        }
        if(str_movimiento.substr(0,7)=="on_hit."
                /*ugly patch for chained on hit*/
                && p->getString("current_move")=="on_hit.air_knockdown")
        {
            p->setEntero("Colision.x",-1000);
            p->setEntero("Colision.y",-1000);
        }
        if(str_movimiento.substr(0,7)=="on_hit."
                /*ugly patch for chained on hit*/
                && p->getString("current_move")!="on_hit.air_knockdown")
        {

            if(p->numero==1)
            {
                hit_cancel_pa=str_movimiento;
                Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
                hit_cancel_pa_damage=m_contrario->damage;
                hit_cancel_pa_chip_damage=m_contrario->chip_damage;
                hit_cancel_pa_unblockable_air=m_contrario->unblockable_air;
                hit_cancel_pa_unblockable_high=m_contrario->unblockable_high;
                hit_cancel_pa_unblockable_low=m_contrario->unblockable_low;
            }
            if(p->numero==2)
            {
                hit_cancel_pb=str_movimiento;
                Movimiento* m_contrario=p->personaje_contrario->movimientos[p->personaje_contrario->getString("current_move")];
                hit_cancel_pb_damage=m_contrario->damage;
                hit_cancel_pb_chip_damage=m_contrario->chip_damage;
                hit_cancel_pb_unblockable_air=m_contrario->unblockable_air;
                hit_cancel_pb_unblockable_high=m_contrario->unblockable_high;
                hit_cancel_pb_unblockable_low=m_contrario->unblockable_low;
            }
        }
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
//                sonido->playSound(p->char_name+str_movimiento);
//                //setear isActive.
//                p->setString(std::string("isActive.")+str_movimiento,"yes");
            }
        }
    }
    //Movimientos continuos
    //agregar nuevos
    for(int i=0; i<(int)p->inputs.size(); i++) //for each movimiento
        if(p->movimientos[p->inputs[i]->movimiento]->is_status)
//            if(p->inputs[i]->input[0]=="*")//buscar los constantes
                if(p->cumpleCondiciones(p->inputs[i]->movimiento))//si cumple
                {
                    bool existe=false;
                    for(int j=0; j<(int)p->movimientos_constantes_actuales.size(); j++) //for each movimiento
                        if(p->movimientos_constantes_actuales[j]->nombre==p->inputs[i]->movimiento)
                        {
                            existe=true;
                        }
                    if(!existe)
                    {
//                        else
//                        {
                            std::string movimiento_temp=p->inputs[i]->movimiento;
                            p->setString(std::string("isActive.")+movimiento_temp,"yes");
                            p->movimientos_constantes_actuales.push_back(p->movimientos[movimiento_temp]);
//                        }
                    }
                }
}

void Fighter::velocityInheritance(Personaje*p,Movimiento*old_move,Movimiento*new_move)
{
    if(old_move->final_velocity_x!=9999)
        p->setEntero("velocity_x",old_move->final_velocity_x);

    if(old_move->final_velocity_y!=9999)
        p->setEntero("velocity_y",old_move->final_velocity_y);

    if(old_move->final_acceleration_x!=9999)
        p->setEntero("acceleration_x",old_move->final_acceleration_x);

    if(old_move->final_acceleration_y!=9999)
        p->setEntero("acceleration_y",old_move->final_acceleration_y);

    if(!new_move->inherits_velocity)
    {
        p->setEntero("velocity_x",new_move->initial_velocity_x);
        p->setEntero("velocity_y",new_move->initial_velocity_y);
        p->setEntero("acceleration_x",new_move->initial_acceleration_x);
        p->setEntero("acceleration_y",new_move->initial_acceleration_y);
    }
}

void Fighter::logica()
{
    //logica proyectiles
    getPaActual()->logicaProyectiles();
    getPbActual()->logicaProyectiles();

    if(is_training)
    {
        if(training_health_regen_frame<=0)
            getPbActual()->heal(5);
        training_health_regen_frame--;
    }

    //verificar si estan atacando
    if(getPaActual()->getMovimientoActual()->is_attack
        || getPaActual()->getString("projectile_active")=="yes")
    {
        getPaActual()->setString("attacking","yes");
    }
    else
    {
        getPaActual()->setString("attacking","no");
    }

    if(getPbActual()->getMovimientoActual()->is_attack
        || getPbActual()->getString("projectile_active")=="yes")
    {
        getPbActual()->setString("attacking","yes");
    }
    else
    {
        getPbActual()->setString("attacking","no");
    }

//    if(getPaActual()->getHitBoxes("red").size()>0
//       || getPaActual()->proyectiles_activos>0)
//    {
//        getPaActual()->setString("attacking","yes");
//    }
//    else
//    {
//        getPaActual()->setString("attacking","no");
//    }
//    if(getPbActual()->getHitBoxes("red").size()>0
//       || getPbActual()->proyectiles_activos>0)
//    {
//        getPbActual()->setString("attacking","yes");
//    }
//    else
//    {
//        getPbActual()->setString("attacking","no");
//    }

    move_cancel_pa="";
    move_cancel_pb="";

    hit_cancel_pa="";
    hit_cancel_pa_damage=0;
    hit_cancel_pa_chip_damage=0;
    hit_cancel_pa_unblockable_air=false;
    hit_cancel_pa_unblockable_high=false;
    hit_cancel_pa_unblockable_low=false;
    hit_cancel_pb="";
    hit_cancel_pb_damage=0;
    hit_cancel_pb_chip_damage=0;
    hit_cancel_pb_unblockable_air=false;
    hit_cancel_pb_unblockable_high=false;
    hit_cancel_pb_unblockable_low=false;

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
        sonido->playSound(p->char_name+move_cancel_pa);
        //setear isActive.
        p->setString(std::string("isActive.")+move_cancel_pa,"yes");

        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        velocityInheritance(p,m,m_nuevo);
        if(p->getString("current_move")=="blockstun.stand")
        {
            p->setEntero("blockstun.current_value",p->personaje_contrario->getMovimientoActual()->blockstun);
            p->setEntero("hp.current_value",p->getEntero("hp.current_value")-p->personaje_contrario->getMovimientoActual()->chip_damage);
        }
        if(p->getString("current_move")=="blockstun.crouch")
        {
            p->setEntero("blockstun.current_value",p->personaje_contrario->getMovimientoActual()->blockstun);
            p->setEntero("hp.current_value",p->getEntero("hp.current_value")-p->personaje_contrario->getMovimientoActual()->chip_damage);
        }

    }

    if(move_cancel_pb!="")
    {
        Personaje* p=getPbActual();
        Movimiento* m=p->movimientos[p->getString("current_move")];
        m->frame_actual=0;
        m->tiempo_transcurrido=0;
        m->ya_pego=false;
        p->setString("current_move",move_cancel_pb);
        sonido->playSound(p->char_name+move_cancel_pb);
        //setear isActive.
        p->setString(std::string("isActive.")+move_cancel_pb,"yes");

        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        velocityInheritance(p,m,m_nuevo);
        if(p->getString("current_move")=="blockstun.stand")
        {
            p->setEntero("blockstun.current_value",p->personaje_contrario->getMovimientoActual()->blockstun);
            p->setEntero("hp.current_value",p->getEntero("hp.current_value")-p->personaje_contrario->getMovimientoActual()->chip_damage);
        }
        if(p->getString("current_move")=="blockstun.crouch")
        {
            p->setEntero("blockstun.current_value",p->personaje_contrario->getMovimientoActual()->blockstun);
            p->setEntero("hp.current_value",p->getEntero("hp.current_value")-p->personaje_contrario->getMovimientoActual()->chip_damage);
        }
    }

    if(hit_cancel_pa!="")
    {
        Personaje*p=getPaActual();
        if(p->getString("current_move").substr(0,7)=="on_hit.")
        {
            if(p->getString("current_move")!="on_hit.knockdown")
                p->combo++;
        }
        Movimiento* m=p->movimientos[p->getString("current_move")];

        if(p->getString("current_move").substr(0,8)!="defense.")
        {
            p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_damage);
        }else
        {
            //exit(0);
            //Unreachable code?
            if(p->getString("current_move")=="defense.air")
            {
                if(hit_cancel_pa_unblockable_air)
                {
                    p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_damage);
                }else
                {
                    p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_chip_damage);
                    p->setEntero("block_stun.current_value",hit_cancel_pb_damage);
                }
            }
            if(p->getString("current_move")=="defense.high")
            {
                if(hit_cancel_pa_unblockable_high)
                {
                    p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_damage);
                }else
                {
                    p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_chip_damage);
                    p->setEntero("block_stun.current_value",hit_cancel_pb_damage);
                }
            }
            if(p->getString("current_move")=="defense.crouch")
            {
                if(hit_cancel_pa_unblockable_low)
                {
                    p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_damage);
                }else
                {
                    p->setEntero("hp.current_value",p->getEntero("hp.current_value")-hit_cancel_pa_chip_damage);
                    p->setEntero("block_stun.current_value",hit_cancel_pb_damage);
                }
            }
        }

        m->frame_actual=0;
        m->tiempo_transcurrido=0;
        m->ya_pego=false;
        p->setString("current_move",hit_cancel_pa);
        p->setString(std::string("isActive.")+hit_cancel_pa,"yes");
        sonido->playSound(p->char_name+p->getString("current_move"));

        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        velocityInheritance(p,m,m_nuevo);
    }

    if(hit_cancel_pb!="")
    {
        Personaje*p=getPbActual();
        if(p->getString("current_move").substr(0,7)=="on_hit.")
        {
            p->combo++;
        }
        Movimiento* m=p->movimientos[p->getString("current_move")];

        p->takeDamage(hit_cancel_pb_damage);

        if(is_training)
        {
            if(p->getEntero("hp.current_value")<=0)
            {
                p->setEntero("hp.current_value",1);
            }
            training_health_regen_frame=60;
        }

        m->frame_actual=0;
        m->tiempo_transcurrido=0;
        m->ya_pego=false;
        p->setString("current_move",hit_cancel_pb);
        p->setString(std::string("isActive.")+hit_cancel_pb,"yes");
        sonido->playSound(p->char_name+p->getString("current_move"));

        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        velocityInheritance(p,m,m_nuevo);
    }


    //aplicar efectos proyectiles
    getPaActual()->aplicarEfectosProyectiles();
    getPbActual()->aplicarEfectosProyectiles();
    //APLICAR MODIFICADORES
    if(!stop_time_pb)
        aplicarModificadores(getPaActual());
    if(!stop_time_pa)
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
    mandatoryModifiers(p,m);

    Frame* f=m->frames[m->frame_actual];
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
    {
        m->tiempo_transcurrido++;
    }
    //verificar fin de movimiento
    if(m->frame_actual==(int)m->frames.size())
    {
        if(m->repeat_from>=0)
        {
            m->frame_actual=m->repeat_from;
            m->tiempo_transcurrido=0;
        }else
        {
            m->ya_pego=false;
            if(p->getString("current_move").substr(0,7)=="on_hit.")
                p->combo=0;
            if(p->getString("current_move")!="ko")
            {
                cancel(p);
            }
            else
            {
                m->frame_actual--;
            }
        }
    }
    //verify blockstun cancel
    if(p->getEntero("blockstun.current_value")==0 && p->getString("current_move")=="blockstun.stand")
    {
        p->setString("current_move","idle.stand");
        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        m_nuevo->frame_actual=0;
        m_nuevo->tiempo_transcurrido=0;
        velocityInheritance(p,m,m_nuevo);
    }
    if(p->getEntero("blockstun.current_value")==0 && p->getString("current_move")=="blockstun.crouch")
    {
        p->setString("current_move","idle.crouch");
        Movimiento* m_nuevo=p->movimientos[p->getString("current_move")];
        m_nuevo->frame_actual=1;
        m_nuevo->tiempo_transcurrido=0;
        velocityInheritance(p,m,m_nuevo);
    }
    //verificar cancel de isActive.
    if(p->getString(std::string("isActive.")+p->getString("current_move"))=="no" && p->getString("current_move")!="idle.stand" && p->getString("current_move")!="idle.land_cancel")
    {
        cancel(p);
    }
    //Movimientos continuos
    //ejecutar existentes
    for(int i=0; i<(int)p->movimientos_constantes_actuales.size(); i++)
    {
        Movimiento* mc=p->movimientos_constantes_actuales[i];
        mandatoryModifiers(p,mc);
        if(p->getString(std::string("isActive.")+p->movimientos_constantes_actuales[i]->nombre)=="no")
        {
            mc->frame_actual=0;
            mc->ya_pego=false;
            p->movimientos_constantes_actuales.erase(p->movimientos_constantes_actuales.begin()+i);
            i--;
            continue;
        }
        Frame* fc=mc->frames[mc->frame_actual];
        if(mc->tiempo_transcurrido==0)
            p->aplicarModificadores(fc->modificadores,p->getString("orientation")=="i");
        //avanzar frame
        if(mc->tiempo_transcurrido==fc->duracion)
        {
            mc->frame_actual++;
            mc->tiempo_transcurrido=0;
        }
        else
        {
            m->tiempo_transcurrido++;
        }
        //verificar fin de movimiento
        if(mc->frame_actual==(int)mc->frames.size())
        {
            mc->frame_actual=0;
            mc->ya_pego=false;
            //pos_a_borrar.push_back(i);
            p->setString(std::string("isActive.")+p->movimientos_constantes_actuales[i]->nombre,"no");
            p->movimientos_constantes_actuales.erase(p->movimientos_constantes_actuales.begin()+i);
            i--;
        }
    }
    //logica de barras
    p->logicaBarras();

    //corregir si se sale x
    int distancia=p->getEntero("position_x")-p->personaje_contrario->getEntero("position_x");
    int dist_max=painter->screen_width-100;
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

    //verificar flip
    if(p->getEntero("position_x")>p->personaje_contrario->getEntero("position_x")
            && (p->getString("current_move")=="idle.stand" || p->getString("current_move")=="idle.crouch" || p->getString("current_move")=="idle.land_cancel")
            )
        p->flipLeft();

    if(p->getEntero("position_x")<p->personaje_contrario->getEntero("position_x")
            && (p->getString("current_move")=="idle.stand" || p->getString("current_move")=="idle.crouch" || p->getString("current_move")=="idle.land_cancel")
            )
        p->flipRight();
}

void Fighter::mandatoryModifiers(Personaje* p, Movimiento* m)
{
    if(m->stop_time_at==m->frame_actual)
    {
        if(p->numero==1)
            stop_time_pa=true;
        if(p->numero==2)
            stop_time_pb=true;
    }

    if(m->resume_time_at==m->frame_actual)
    {
        if(p->numero==1)
            stop_time_pa=false;
        if(p->numero==2)
            stop_time_pb=false;
    }

    int orientation_miltiplier=1;
    if(p->getString("orientation")=="i")
        orientation_miltiplier=-1;

    //Push and move
    if(p->getEntero("velocity_x")<0 || p->getString("colision.blue_to_blue")!="yes" || !m->pushes)//No push
    {
        p->setEntero("position_x",p->getEntero("position_x")+p->getEntero("velocity_x")*orientation_miltiplier);
    }else//Push
    {
        p->setEntero("position_x",p->getEntero("position_x")+p->getEntero("velocity_x")*orientation_miltiplier/2);
        p->personaje_contrario->setEntero("position_x",p->personaje_contrario->getEntero("position_x")+p->getEntero("velocity_x")*orientation_miltiplier/2);
    }
    p->setEntero("position_y",p->getEntero("position_y")+p->getEntero("velocity_y"));

    //Separate blue
    if(p->getString("colision.blue_to_blue")=="yes" && !p->personaje_contrario->getMovimientoActual()->pushes)
    {
        p->setEntero("position_x",p->getEntero("position_x")-m->separate_blue*orientation_miltiplier);
        p->personaje_contrario->setEntero("position_x",p->personaje_contrario->getEntero("position_x")+m->separate_blue*orientation_miltiplier/2);
    }
    //Separate red
    int marco_x=50;
    if(p->getString("colision.red_to_blue")=="yes" && !p->personaje_contrario->getMovimientoActual()->pushes)
    {
        //p->setEntero("position_x",p->getEntero("position_x")-m->separate_red*orientation_miltiplier);
        int personaje_contrario_pos_ant = p->personaje_contrario->getEntero("position_x");
        p->personaje_contrario->setEntero("position_x",p->personaje_contrario->getEntero("position_x")+m->separate_red*orientation_miltiplier/2);

        if(p->personaje_contrario->getEntero("position_x")<-stage->size/2+painter->screen_width/2+marco_x)//pa borde izquierdo
        {
            p->setEntero("position_x",p->getEntero("position_x")-m->separate_red*orientation_miltiplier/2);
            p->personaje_contrario->setEntero("position_x",personaje_contrario_pos_ant);
        }
        if(p->personaje_contrario->getEntero("position_x")>stage->size/2+painter->screen_width/2-marco_x)//pa borde derecho
        {
            p->setEntero("position_x",p->getEntero("position_x")-m->separate_red*orientation_miltiplier/2);
            p->personaje_contrario->setEntero("position_x",personaje_contrario_pos_ant);
        }
    }

    int new_velocity_x = p->getEntero("velocity_x") + p->getEntero("acceleration_x");
    int new_velocity_y = p->getEntero("velocity_y") + p->getEntero("acceleration_y");

    if(m->friction)
    {
        if((new_velocity_x > 0 && p->getEntero("velocity_x") > 0)
           || (new_velocity_x < 0 && p->getEntero("velocity_x") < 0)
            )
        {
            p->setEntero("velocity_x",new_velocity_x);
        }else
        {
            p->setEntero("velocity_x",0);
            p->setEntero("acceleration_x",0);
        }

        p->setEntero("velocity_y",new_velocity_y);

    }else
    {
        p->setEntero("velocity_x",new_velocity_x);
        p->setEntero("velocity_y",new_velocity_y);
    }

}

void Fighter::logicaStage()
{
    int pa_x=getPaActual()->getEntero("position_x");
    int pb_x=getPbActual()->getEntero("position_x");
    int marco_x=50;

    //verificar q los personajes no se salgan
    if(pa_x<-stage->size/2+painter->screen_width/2+marco_x)//pa borde izquierdo
    {
        pa_x=-stage->size/2+painter->screen_width/2+marco_x;
        getPaActual()->setEntero("position_x",pa_x);
    }
    if(pa_x>stage->size/2+painter->screen_width/2-marco_x)//pa borde derecho
    {
        pa_x=stage->size/2+painter->screen_width/2-marco_x;
        getPaActual()->setEntero("position_x",pa_x);
    }
    if(pb_x<-stage->size/2+painter->screen_width/2+marco_x)//pb borde izquierdo
    {
        pb_x=-stage->size/2+painter->screen_width/2+marco_x;
        getPbActual()->setEntero("position_x",pb_x);
    }
    if(pb_x>stage->size/2+painter->screen_width/2-marco_x)//pb borde derecho
    {
        pb_x=stage->size/2+painter->screen_width/2-marco_x;
        getPbActual()->setEntero("position_x",pb_x);
    }

    //New camera position
    int nueva_pos=(pa_x+pb_x)/2-painter->screen_width/2;

    if(nueva_pos<-stage->size/2+painter->screen_width/2)
        nueva_pos=-stage->size/2+painter->screen_width/2;

    if(nueva_pos>stage->size/2-painter->screen_width/2)
        nueva_pos=stage->size/2-painter->screen_width/2;

    painter->camera_x=nueva_pos;

    //Alineacion y
    int y_max=getPaActual()->getEntero("position_y");
    if(y_max<getPbActual()->getEntero("position_y"))
        y_max=getPbActual()->getEntero("position_y");

    painter->camera_y=y_max/4;


    if(!camera_effect_x.empty())
    {
        painter->camera_x+=camera_effect_x.front();
        camera_effect_x.pop();
    }

    if(!camera_effect_y.empty())
    {
        painter->camera_y+=camera_effect_y.front();
        camera_effect_y.pop();
    }
}

void Fighter::loopJuego()
{
    getPaActual()->comparacion_hp=getPaActual()->getEntero("hp.current_value");
    getPaActual()->comparacion_hp_contrario=getPbActual()->getEntero("hp.current_value");

    getPbActual()->comparacion_hp=getPbActual()->getEntero("hp.current_value");
    getPbActual()->comparacion_hp_contrario=getPbActual()->getEntero("hp.current_value");

    //sonido->playSound("Stage.music",true);
    //u32 anterior=painter->device->getTimer()->getTime();
    for (;;)
    {
        //cout<<getPaActual()->input->getBufferRosalilaInputss()[0]<<"\t";
        //cout<<getPbActual()->input->getBufferRosalilaInputss()[0]<<endl;
        //Salir con cualquier boton si ya termino la pelea
        if(game_over_a || game_over_b)
        {
            std::string last_input=getPaActual()->input->getBufferRosalilaInputs()[0];
            if(last_input!="1"
               && last_input!="2"
               && last_input!="3"
               && last_input!="4"
               && last_input!="5"
               && last_input!="6"
               && last_input!="7"
               && last_input!="8"
               && last_input!="9"
               && ((getPaActual()->getString("current_move")=="idle.stand"
                    ||getPbActual()->getString("current_move")=="idle.stand")
                    || (getPaActual()->getString("current_move")=="victory"
                            && getPaActual()->getMovimientoActual()->frame_actual==(int)getPaActual()->getMovimientoActual()->frames.size()-1)
                    || (getPbActual()->getString("current_move")=="victory"
                            && getPbActual()->getMovimientoActual()->frame_actual==(int)getPbActual()->getMovimientoActual()->frames.size()-1)
                  )
               )
                break;

            last_input=getPbActual()->input->getBufferRosalilaInputs()[0];
            if(last_input!="1"
               && last_input!="2"
               && last_input!="3"
               && last_input!="4"
               && last_input!="5"
               && last_input!="6"
               && last_input!="7"
               && last_input!="8"
               && last_input!="9"
               && ((getPbActual()->getString("current_move")=="idle.stand"
                    ||getPbActual()->getString("current_move")=="idle.stand")
                    || (getPbActual()->getString("current_move")=="victory"
                            && getPbActual()->getMovimientoActual()->frame_actual==(int)getPbActual()->getMovimientoActual()->frames.size()-1)
                    || (getPbActual()->getString("current_move")=="victory"
                            && getPbActual()->getMovimientoActual()->frame_actual==(int)getPbActual()->getMovimientoActual()->frames.size()-1)
                  )
               )
                break;
        }

        if(receiver->isKeyPressed(SDLK_ESCAPE))///!!!
        {
            pause_menu->loopMenu();
            if(pause_menu->getExitSignal())
                break;
        }

        //anterior=painter->device->getTimer()->getTime();

        //logica
        logica();

        //render


//        //Caption test inputs
//        RosalilaInputs*input=getPaActual()->input;
//        std::string caption = input->getBufferRosalilaInputss()[0]+"-"+input->getBufferRosalilaInputss()[1]+"-"+input->getBufferRosalilaInputss()[2]+"-"+input->getBufferRosalilaInputss()[3];
//        SDL_WM_SetCaption( caption.c_str(), NULL );


        render();
        //receiver->startEventProcess();
    }
}

void Fighter::dibujarBarra()
{
    painter->draw2DImage
    (   texture_bar,
        texture_bar->getWidth(),texture_bar->getHeight(),
        painter->screen_width/2-texture_bar->getWidth()/2,0,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        0,0,
        false);

    for(int i=0;i<victories_a;i++)
    {
        int separation_x=texture_victory->getWidth();
        painter->draw2DImage
        (   texture_victory,
            texture_victory->getWidth(),texture_victory->getHeight(),
            painter->screen_width/2-texture_victory->getWidth()/2-victory_image_x-i*separation_x,victory_image_y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false);
    }

    for(int i=0;i<victories_b;i++)
    {
        int separation_x=texture_victory->getWidth();
        painter->draw2DImage
        (   texture_victory,
            texture_victory->getWidth(),texture_victory->getHeight(),
            painter->screen_width/2-texture_victory->getWidth()/2+victory_image_x+i*separation_x,victory_image_y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false);
    }
}

void Fighter::printHitboxes()
{
    getPaActual()->dibujarHitBoxes("blue","",getPaActual()->getString("orientation")=="i",getPaActual()->getEntero("position_x"),getPaActual()->getEntero("position_y"));
    getPbActual()->dibujarHitBoxes("blue","",getPbActual()->getString("orientation")=="i",getPbActual()->getEntero("position_x"),getPbActual()->getEntero("position_y"));
    getPaActual()->dibujarHitBoxes("red","",getPaActual()->getString("orientation")=="i",getPaActual()->getEntero("position_x"),getPaActual()->getEntero("position_y"));
    getPbActual()->dibujarHitBoxes("red","",getPbActual()->getString("orientation")=="i",getPbActual()->getEntero("position_x"),getPbActual()->getEntero("position_y"));
}

void Fighter::printBuffer()
{
    for(int i=0;i<(int)getPaActual()->input->getBufferRosalilaInputs().size();i++)
    {
        string input_iterator = getPaActual()->input->getBufferRosalilaInputs()[i];
        for(int j=0;j<(int)input_iterator.size();j++)
        {
            painter->draw2DImage
            (   input_buffer_images[input_iterator[j]],
                50,50,
                50*(20-i),50*j,
                1.0,
                0.0,
                false,
                0,0,
                Color(255,255,255,255),
                0,0,
                false);
        }
    }

    for(int i=0;i<(int)getPaActual()->input->getPrintableBufferRosalilaInputs().size();i++)
    {
        string input_iterator = getPaActual()->input->getPrintableBufferRosalilaInputs()[i];
        for(int j=0;j<(int)input_iterator.size();j++)
        {
            painter->draw2DImage
            (   input_buffer_images[input_iterator[j]],
                50,50,
                50*(20-i),50*j+100,
                1.0,
                0.0,
                false,
                0,0,
                Color(255,255,255,255),
                0,0,
                false);
        }
    }
}

void Fighter::render()
{
    //Stage
    stage->dibujarBack(stop_time_pa || stop_time_pb);

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
    if(receiver->isKeyPressed(SDLK_h))
        hitboxes_are_visible=!hitboxes_are_visible;

    if(hitboxes_are_visible)
        printHitboxes();


    getPaActual()->dibujarProyectiles();
    getPbActual()->dibujarProyectiles();

    stage->dibujarFront(stop_time_pa || stop_time_pb);

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

    if(game_over_a && getPaActual()->getString("current_move")!="ko" && getPbActual()->getString("current_move")=="idle.stand")
    {
        //cancelar anterior
        Personaje*p=getPaActual();
        p->combo=0;
        p->personaje_contrario->combo=0;
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
        m=getPaActual()->movimientos[p->getString("current_move")];
        m->frame_actual=0;
        m->tiempo_transcurrido=0;
        m->ya_pego=false;
        getPaActual()->setEntero("velocity_x",0);
        getPaActual()->setEntero("velocity_y",0);
        getPaActual()->setEntero("acceleration_x",0);
        getPaActual()->setEntero("acceleration_x",0);
        getPaActual()->setString("isActive.ko","yes");

        if(!game_over_b)
        {
            getPbActual()->setString("current_move","victory");
            getPbActual()->setString("isActive.victory","yes");
        }
    }

    if(game_over_b && getPbActual()->getString("current_move")!="ko" && getPaActual()->getString("current_move")=="idle.stand")
    {
        //cancelar anterior
        Personaje*p=getPaActual();
        p->combo=0;
        p->personaje_contrario->combo=0;
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
        m=getPbActual()->movimientos[p->getString("current_move")];
        m->frame_actual=0;
        m->tiempo_transcurrido=0;
        m->ya_pego=false;
        getPbActual()->setEntero("velocity_x",0);
        getPbActual()->setEntero("velocity_y",0);
        getPbActual()->setEntero("acceleration_x",0);
        getPbActual()->setEntero("acceleration_x",0);
        getPbActual()->setString("isActive.ko","yes");

        if(!game_over_a)
        {
            getPaActual()->setString("current_move","victory");
            getPaActual()->setString("isActive.victory","yes");
        }
    }

    if(game_over_a || game_over_b)
    {
        if(ko.size()>0)
        {
            Image* texture_gameover=ko[pos_imagen_ko]->imagen;
            tiempo_actual_ko++;
            if(tiempo_actual_ko==duracion_ko)
            {
                pos_imagen_ko++;
                tiempo_actual_ko=0;
            }
            if(pos_imagen_ko>=(int)ko.size())
                pos_imagen_ko=0;
            painter->draw2DImage
            (   texture_gameover,
                texture_gameover->getWidth(),texture_gameover->getHeight(),
                (painter->screen_width-texture_gameover->getWidth())/2,(painter->screen_height-texture_gameover->getHeight())/2,
                1.0,
                0.0,
                false,
                0,0,
                Color(255,255,255,255),
                0,0,
                false);
        }
    }


    if(pos_imagen_intro<(int)match_intro.size() && pa[0]->getString("current_move")=="idle.stand" && pb[0]->getString("current_move")=="idle.stand")
    {
        //Image* texture_gameover=grafico->getTexture("misc/ko/1.png");
        Image* texture_gameover=match_intro[pos_imagen_intro]->imagen;
        tiempo_actual_intro++;
        if(tiempo_actual_intro==duracion_intro)
        {
            pos_imagen_intro++;
            tiempo_actual_intro=0;
        }
        painter->draw2DImage
        (   texture_gameover,
            texture_gameover->getWidth(),texture_gameover->getHeight(),
            (painter->screen_width-texture_gameover->getWidth())/2,(painter->screen_height-texture_gameover->getHeight())/2,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
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

    painter->draw3D();

    dibujarBarra();

    if(pa[pa_actual]->combo>1)
        painter->drawText(toString(pa[pa_actual]->combo)+" hits",50,200);
    if(pb[pb_actual]->combo>1)
        painter->drawText(toString(pb[pb_actual]->combo)+" hits",painter->screen_width-300,200);

    if(counter_pa_visible_frame>0)
        painter->drawText("Counter!",50,300);
    if(counter_pb_visible_frame>0)
        painter->drawText("Counter!",painter->screen_width-400,300);

    counter_pb_visible_frame--;
    counter_pa_visible_frame--;

    if(receiver->isKeyPressed(SDLK_1))
        distance_is_visible=!distance_is_visible;
    if(distance_is_visible)
        painter->drawText(toString(getPaActual()->getEntero("distance_absolute")),painter->screen_width/2-100,0);

    if(receiver->isKeyPressed(SDLK_2))
        buffer_is_visible=!buffer_is_visible;
    if(buffer_is_visible)
        printBuffer();

    if(receiver->isKeyPressed(SDLK_3))
        fps_is_visible=!fps_is_visible;

    if(fps_is_visible)
        painter->drawText("FPS: "+toString(painter->getFrameCap()),0,0);

    receiver->updateInputs();
    painter->updateScreen();
}

void Fighter::applyCameraEffect()
{

    for(int i=6;i>0;i--)
    {
        if(i%2==0)
            for(int j=0;j<i;j++)
                camera_effect_y.push(j*15);
        else
            for(int j=0;j<i;j++)
                camera_effect_y.push(-j*15);
    }

}
