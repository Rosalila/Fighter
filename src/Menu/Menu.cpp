#include "Menu/Menu.h"
Menu::Menu(Painter* painter,Receiver* receiver,Sonido* sonido,char* archivo)
{
    this->painter=painter;
    this->receiver=receiver;
    this->sonido=sonido;
    this->exit_signal=false;
    this->save_inputs_signal=false;
    this->char_select=NULL;

    vs_screen=painter->getTexture("misc/vs_screen.png");

    TiXmlDocument doc_t((char*)"config.xml");
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    std::vector<std::string> chars,stages;
    for(TiXmlNode* node_chars=doc->FirstChild("Chars");
            node_chars!=NULL;
            node_chars=node_chars->NextSibling("Chars"))
    {
        for(TiXmlNode* node_chars2=node_chars->FirstChild("char");
                node_chars2!=NULL;
                node_chars2=node_chars2->NextSibling("char"))
        {
            chars.push_back(std::string(node_chars2->ToElement()->Attribute("nombre")));
        }
    }

    for(TiXmlNode* node_chars=doc->FirstChild("Stages");
            node_chars!=NULL;
            node_chars=node_chars->NextSibling("Stages"))
    {
        for(TiXmlNode* node_chars2=node_chars->FirstChild("stage");
                node_chars2!=NULL;
                node_chars2=node_chars2->NextSibling("stage"))
        {
            stages.push_back(std::string(node_chars2->ToElement()->Attribute("nombre")));
        }
    }

    cargarDesdeXml(archivo,chars,stages);
}

void Menu::iniciarJuego(int num_personajes,bool inteligencia_artificial)
{
    writeLogLine("Initializing game.");
    if(inteligencia_artificial)
        char_select->lockPB(0);
    printVsScreen(char_select->getLockedPreviewsPA(),char_select->getLockedPreviewsPB());

    pa.clear();
    pb.clear();

    writeLogLine("Initializing stage.");

    stage=new Stage(painter,sonido);

    stage->cargarDesdeXML(getStage());

    for(int i=0;i<num_personajes;i++)
    {
        Personaje* p1a=getPersonajeA(i,false);
        Personaje* p1b=getPersonajeB(i,inteligencia_artificial);
        p1a->personaje_contrario=p1b;
        p1b->personaje_contrario=p1a;
        pa.push_back(p1a);
        pb.push_back(p1b);
    }

    sonido->stopMusic();

    sonido->playMusic(stage->music_path);

    Fighter*fighter=NULL;

    int pa_victories=0;
    int pb_victories=0;

    for(int current_round=0;;current_round++)
    {
        fighter=new Fighter(sonido,painter,receiver,pa,pb,stage,pa_victories,pb_victories);

        if(fighter->game_over_a && fighter->game_over_b)
        {
            pa_victories++;
            pb_victories++;
        }
        else if(fighter->game_over_a)
            pb_victories++;
        else if(fighter->game_over_b)
            pa_victories++;
        else//salir en el menu de pausa
        {
//            delete fighter;
            break;
        }

        for(int i=0;i<num_personajes;i++)
        {
            Personaje* p1a=pa[i];
            Personaje* p1b=pb[i];
            p1a->resetPersonaje();
            p1b->resetPersonaje();
        }
//        delete fighter;
        //Finish game
        if(pa_victories>=rounds && pb_victories>=rounds)
        {
            Menu *temp=new Menu(painter,receiver,sonido,"menu/draw.xml");
            temp->loopMenu();
            break;
        }
        else if(pa_victories>=rounds)
        {
            Menu *temp=new Menu(painter,receiver,sonido,"menu/pa_wins.xml");
            temp->loopMenu();
            break;
        }
        else if(pb_victories>=rounds)
        {
            Menu *temp=new Menu(painter,receiver,sonido,"menu/pb_wins.xml");
            temp->loopMenu();
            break;
        }
    }

    delete fighter;

    char_select->clearLocks();

    sonido->stopMusic();

    sonido->playMusic((std::string)"menu/audio/music.ogg");
}

void Menu::loopMenu()
{
    bool tecla_arriba=false;

    llenarInputsBotones();
    inputa=new Input();
    inputb=new Input();
    inputa->cargarDesdeXML(1,receiver);
    inputb->cargarDesdeXML(2,receiver);
    bool tecla_arriba_p1=true;
    bool tecla_arriba_p2=true;
    //inicio
	for (;;)
	{

        dibujarMenu();

        //Move Elements
        for(int i=0;i<(int)elementos.size();i++)
        {
            Elemento*e=elementos[i];
            if(e->getTipo()==2)//Is MenuImagen
            {
                MenuImagen* mi=(MenuImagen*)e;
                if(mi->fade_in_current!=-1)
                {
                    mi->fade_in_current+=mi->fade_in_speed;
                    if(mi->fade_in_current>255)
                        mi->fade_in_current=255;
                }
            }
            if(e->current_displacement_x<e->stop_displacement_x_at)
            {
                e->x+=e->displacement_x;
                e->current_displacement_x++;
            }
            if(e->current_displacement_y<e->stop_displacement_y_at)
            {
                e->y+=e->displacement_y;
                e->current_displacement_y++;
            }
        }

        inputa->actualizarBuffer();
        if(inputa->getBufferInputs()[0]!="6"
           && inputa->getBufferInputs()[0]!="4"
           && inputa->getBufferInputs()[0]!="2"
           && inputa->getBufferInputs()[0]!="8"
           && inputa->getBufferInputs()[0]!="a"
           )
        {
            tecla_arriba_p1=true;
        }
        if(char_select!=NULL && tecla_arriba_p1)
        {
            if(char_select->listoPA())
            {
            }else if(inputa->getBufferInputs()[0]=="6")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p1_x++;
                if(char_select->select_p1_x>=char_select->size_x)
                    char_select->select_p1_x=0;
                tecla_arriba_p1=false;
            }else if(inputa->getBufferInputs()[0]=="4")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p1_x--;
                if(char_select->select_p1_x<0)
                    char_select->select_p1_x=char_select->size_x-1;
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="2")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p1_y++;
                if(char_select->select_p1_y>=char_select->size_y)
                    char_select->select_p1_y=0;
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="8")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p1_y--;
                if(char_select->select_p1_y<0)
                    char_select->select_p1_y=char_select->size_y-1;
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="a")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(0);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="b")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(1);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="c")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(2);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="d")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(3);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="e")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(4);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="f")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(5);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="g")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(6);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="h")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPA(7);
                tecla_arriba_p1=false;
            }
        }

        inputb->actualizarBuffer();
        if(inputb->getBufferInputs()[0]!="6"
           && inputb->getBufferInputs()[0]!="4"
           && inputb->getBufferInputs()[0]!="2"
           && inputb->getBufferInputs()[0]!="8"
           && inputb->getBufferInputs()[0]!="a"
           )
        {
            tecla_arriba_p2=true;
        }
        if(char_select!=NULL && tecla_arriba_p2)
        {
            if(char_select->listoPB())
            {
            }else if(inputb->getBufferInputs()[0]=="6")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p2_x++;
                if(char_select->select_p2_x>=char_select->size_x)
                    char_select->select_p2_x=0;
                tecla_arriba_p2=false;
            }else if(inputb->getBufferInputs()[0]=="4")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p2_x--;
                if(char_select->select_p2_x<0)
                    char_select->select_p2_x=char_select->size_x-1;
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="2")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p2_y++;
                if(char_select->select_p2_y>=char_select->size_y)
                    char_select->select_p2_y=0;
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="8")
            {
                sonido->reproducirSonido(std::string("Menu.move_char"),false);
                char_select->select_p2_y--;
                if(char_select->select_p2_y<0)
                    char_select->select_p2_y=char_select->size_y-1;
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="a")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(0);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="b")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(1);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="c")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(2);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="d")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(3);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="e")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(4);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="f")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(5);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="g")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(6);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="h")
            {
                sonido->reproducirSonido(std::string("Menu.select_char"),false);
                char_select->lockPB(7);
                tecla_arriba_p2=false;
            }
        }
        if(!receiver->IsKeyDownn(SDLK_LEFT)
           && !receiver->IsKeyDownn(SDLK_RIGHT)
           && !receiver->IsKeyDownn(SDLK_UP)
           && !receiver->IsKeyDownn(SDLK_DOWN)
           && !receiver->IsKeyDownn(SDLK_RETURN)
           && !receiver->IsKeyDownn(SDLK_ESCAPE)
           )
            tecla_arriba=true;
        if(tecla_arriba)
        {
            tecla_arriba=false;
            if(receiver->IsKeyDownn(SDLK_ESCAPE))
            {
                sonido->reproducirSonido(std::string("Menu.back"),false);
                exit_signal=true;
                break;
            }
            else if(receiver->IsKeyDownn(SDLK_DOWN))
            {
                sonido->reproducirSonido(std::string("Menu.move"),false);
                ((MenuContenedor*)contenedor_actual)->avanzar();
            }
            else if(receiver->IsKeyDownn(SDLK_UP))
            {
                sonido->reproducirSonido(std::string("Menu.move"),false);
                ((MenuContenedor*)contenedor_actual)->retroceder();
            }
            else if(receiver->IsKeyDownn(SDLK_RIGHT))
            {
                sonido->reproducirSonido(std::string("Menu.move"),false);
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==5)
                {
                    MenuLista* ml=((MenuLista*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    ml->avanzar();
//                    if(ml->getAccion()==0)
//                    {
//                        MenuTexto*mt=(MenuTexto*)ml->getElementoActual();
//                        //convert to char*
//                        size_t count = 255;
//                        c8* str_ptr= (char*)malloc( 255 );
//                        wcstombs(str_ptr, mt->texto.c_str(), count);
//
//                        time=atoi(str_ptr);
//                    }
//                    if(ml->getAccion()==1)
//                    {
//                        MenuTexto*mt=(MenuTexto*)ml->getElementoActual();
//                        //convert to char*
//                        size_t count = 255;
//                        c8* str_ptr= (char*)malloc( 255 );
//                        wcstombs(str_ptr, mt->texto.c_str(), count);
//
//                        rounds=atoi(str_ptr);
//                    }
                }
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==6)
                {
                    MenuBarra* mb=((MenuBarra*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    mb->avanzar();
                    if(mb->getAccion()==0)
                    {
                        ai_level=mb->actual;
                    }
                }
            }
            else if(receiver->IsKeyDownn(SDLK_LEFT))
            {
                sonido->reproducirSonido(std::string("Menu.move"),false);
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==5)
                {
                    MenuLista* ml=((MenuLista*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    ml->retroceder();
//                    if(ml->getAccion()==0)
//                    {
//                        MenuTexto*mt=(MenuTexto*)ml->getElementoActual();
//                        //convert to char*
//                        size_t count = 255;
//                        c8* str_ptr= (char*)malloc( 255 );
//                        wcstombs(str_ptr, mt->texto.c_str(), count);
//
//                        time=atoi(str_ptr);
//                    }
//                    if(ml->getAccion()==1)
//                    {
//                        MenuTexto*mt=(MenuTexto*)ml->getElementoActual();
//                        //convert to char*
//                        size_t count = 255;
//                        c8* str_ptr= (char*)malloc( 255 );
//                        wcstombs(str_ptr, mt->texto.c_str(), count);
//
//                        rounds=atoi(str_ptr);
//                    }
                }
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==6)
                {
                    MenuBarra* mb=((MenuBarra*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    mb->retroceder();
                    if(mb->getAccion()==0)
                    {
                        ai_level=mb->actual;
                    }
                }
            }else if(receiver->IsKeyPressed(SDLK_RETURN))
            {
                sonido->reproducirSonido(std::string("Menu.select"),false);
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==5)
                {
                    MenuLista*ml=((MenuLista*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    if(ml->getAccion()==0)
                        if(char_select->listo())
                            iniciarJuego(1,false);
                    if(ml->getAccion()==1)
                        if(char_select->listo())
                            iniciarJuego(2,false);
                    if(ml->getAccion()==3)
                        if(char_select->listo())
                            iniciarJuego(3,false);
                    if(ml->getAccion()==4)
                        if(char_select->listoPA())
                            iniciarJuego(1,true);
                    if(ml->getAccion()==5)
                        if(char_select->listoPA())
                            iniciarJuego(2,true);
                    if(ml->getAccion()==6)
                        if(char_select->listoPA())
                            iniciarJuego(3,true);
                }
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==4)
                {
                    MenuBoton*mb=((MenuBoton*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    if(mb->getAccion()==0)
                    {
                        if(char_select->listo())
                        {
                            iniciarJuego(1,false);
                        }
                    }

                    if(mb->getAccion()==1)
                    {
                        if(char_select->listo())
                        {
                            iniciarJuego(3,true);
                        }
                    }
                    if(mb->getAccion()==2)
                    {
                        break;
                    }
                    if(mb->getAccion()==3)
                    {
                        exit_signal=true;
                        break;
                    }
                    if(mb->getAccion()==4)
                    {
                        Menu *temp=new Menu(painter,receiver,sonido,mb->load_menu);
                        temp->loopMenu();
                    }
                    if(mb->getAccion()==5)
                    {
                        if(char_select->listo())
                        {
                            printVsScreen(char_select->getLockedPreviewsPA(),char_select->getLockedPreviewsPB());

                            Personaje* p1a=getPersonajeA(0,false);
                            Personaje* p1b=getPersonajeB(0,false);
                            p1a->personaje_contrario=p1b;
                            p1b->personaje_contrario=p1a;

                            p1a->setEntero("hp.periodic_modifier",1);
                            p1a->setEntero("hp.period",1);
                            p1b->setEntero("hp.periodic_modifier",1);
                            p1b->setEntero("hp.period",1);
                            Input*i_temp=new Input();
//                            i_temp->cargarIAXML(2,(char*)"");
//                            p1b->input=i_temp;

                            Personaje* p2a=getPersonajeA(1,false);
                            Personaje* p2b=getPersonajeB(1,false);
                            p2a->personaje_contrario=p1b;
                            p2b->personaje_contrario=p1a;

                            p2a->setEntero("hp.periodic_modifier",1);
                            p2a->setEntero("hp.period",1);
                            p2b->setEntero("hp.periodic_modifier",1);
                            p2b->setEntero("hp.period",1);
                            i_temp=new Input();
//                            i_temp->cargarIAXML(2,(char*)"");
//                            p2b->input=i_temp;

                            Personaje* p3a=getPersonajeA(2,false);
                            Personaje* p3b=getPersonajeB(2,false);
                            p3a->personaje_contrario=p1b;
                            p3b->personaje_contrario=p1a;

                            p3a->setEntero("hp.periodic_modifier",1);
                            p3a->setEntero("hp.period",1);
                            p3b->setEntero("hp.periodic_modifier",1);
                            p3b->setEntero("hp.period",1);
                            i_temp=new Input();
//                            i_temp->cargarIAXML(2,(char*)"");
//                            p3b->input=i_temp;

                            pa.push_back(p1a);
                            pa.push_back(p2a);
                            pa.push_back(p3a);

                            pb.push_back(p1b);
                            pb.push_back(p2b);
                            pb.push_back(p3b);

                            stage=new Stage(painter,sonido);
                            stage->cargarDesdeXML(getStage());

                            sonido->stopMusic();
                            Fighter*fighter=new Fighter(sonido,painter,receiver,pa,pb,stage,0,0);
                            delete fighter;
                            sonido->playMusic("menu/audio/music.ogg");

                            break;
                        }
                    }
                    if(mb->getAccion()==6)
                    {
                        if(char_select->listo())
                        {
                            iniciarJuego(2,false);
                        }
                    }
                    if(mb->getAccion()==7)
                    {
                        if(char_select->listo())
                        {
                            iniciarJuego(3,false);
                        }
                    }
                    if(mb->getAccion()==8)//save config
                    {
                        TiXmlDocument *doc=new TiXmlDocument();
                        TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
                        doc->LinkEndChild( decl );

                        TiXmlElement * root = new TiXmlElement("ConfigFile");
                        TiXmlElement * ai = new TiXmlElement("AILevel");
                        ai->SetDoubleAttribute("level",ai_level);
                        TiXmlElement * mt = new TiXmlElement("MatchTime");
                        mt->SetDoubleAttribute("seconds",time);
                        TiXmlElement * r = new TiXmlElement("Rounds");
                        r->SetDoubleAttribute("rounds",rounds);
                        root->LinkEndChild(ai);
                        root->LinkEndChild(mt);
                        root->LinkEndChild(r);
                        doc->LinkEndChild(root);

                        doc->SaveFile("misc/config.xml");
                    }
                    if(mb->getAccion()>=10 && mb->getAccion()<=29)
                    {
                        int player;
                        std::string mapeo="";
                        int accion=mb->getAccion();
                        if(accion>=10 && accion<=19)
                            player=1;
                        else
                            player=2;
                        Input* temp=new Input();
                        Input* temp2=new Input();
                        if(player==1)
                        {
                            temp->cargarDesdeXML(1,receiver);
                            temp2->cargarDesdeXML(2,receiver);
                        }else
                        {
                            temp->cargarDesdeXML(2,receiver);
                            temp2->cargarDesdeXML(1,receiver);
                        }
                        if(accion==10||accion==20)mapeo="8";
                        if(accion==11||accion==21)mapeo="2";
                        if(accion==12||accion==22)mapeo="4";
                        if(accion==13||accion==23)mapeo="6";
                        if(accion==14||accion==24)mapeo="a";
                        if(accion==15||accion==25)mapeo="b";
                        if(accion==16||accion==26)mapeo="c";
                        if(accion==17||accion==27)mapeo="d";
                        if(accion==18||accion==28)mapeo="e";
                        if(accion==19||accion==29)mapeo="f";

                        mb->input_config="";
                        std::string str_input=getInputPressed();
                        //key
                        if((char)str_input[0]!='j')
                        {
                            int pos=-1,posc=-1;
                            for(int j=0;j<(int)temp->botones.size();j++)
                                if(temp->botones[j].getMapeo()==mapeo && !temp->botones[j].usaJoystick())
                                    pos=j;

                            for(int j=0;j<(int)temp->cruz.size();j++)
                                if(temp->cruz[j].getMapeo()==mapeo && !temp->cruz[j].usaJoystick())
                                    posc=j;

                            Boton b(receiver,toKeyCode(str_input),mapeo);
                            if(pos!=-1)
                                temp->botones[pos]=b;
                            else if (posc!=-1)
                                temp->cruz[posc]=b;
                            else
                                temp->botones.push_back(b);
                        }else//joy
                        {
                            int pos=-1,posc=-1;
                            for(int j=0;j<(int)temp->botones.size();j++)
                                if(temp->botones[j].getMapeo()==mapeo && temp->botones[j].usaJoystick())
                                    pos=j;

                            for(int j=0;j<(int)temp->cruz.size();j++)
                                if(temp->cruz[j].getMapeo()==mapeo && temp->cruz[j].usaJoystick())
                                    posc=j;

                            int int_input=((int)(str_input[3]))-48;
                            if((char)str_input[3]=='u')
                                int_input=-8;
                            if((char)str_input[3]=='d')
                                int_input=-2;
                            if((char)str_input[3]=='l')
                                int_input=-4;
                            if((char)str_input[3]=='r')
                                int_input=-6;
                            Boton b(receiver,int_input,((int)str_input[1])-48,mapeo);
                            if(pos!=-1)
                            {
                                temp->botones[pos]=b;
                            }else if(posc!=-1)
                            {
                                temp->cruz[posc]=b;
                            }else
                            {
                                temp->botones.push_back(b);
                            }
                        }

                        escribirInputsXML(temp,temp2);
                        //mb->input_config=b.keyToString();
                        llenarInputsBotones();
                    }
                }
            }else
            {
                tecla_arriba=true;
            }
        }
	}
}

void Menu::dibujarMenu()
{
    for(int i=0;i<(int)elementos.size();i++)
        elementos[i]->dibujar();

    receiver->updateInputs();
    painter->updateScreen();
}

void Menu::cargarConfig()
{
    TiXmlDocument doc_t("misc/config.xml");
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;
    TiXmlNode* node=doc->FirstChild("ConfigFile");
    TiXmlElement* ai_elem=node->FirstChild("AILevel")->ToElement();
    TiXmlElement* time_elem=node->FirstChild("MatchTime")->ToElement();
    TiXmlElement* rounds_elem=node->FirstChild("Rounds")->ToElement();

    ai_level=atoi(ai_elem->Attribute("level"));
    time=atoi(time_elem->Attribute("seconds"));
    rounds=atoi(rounds_elem->Attribute("rounds"));
}

void Menu::cargarDesdeXml(char* archivo,vector<std::string> chars,vector<std::string> stages)
{
    music_path="menu/audio/music.ogg";

    cargarConfig();

    TiXmlDocument doc_t( archivo );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    sonido->agregarSonido("Menu.select","menu/audio/select.ogg");
    sonido->agregarSonido("Menu.select_char","menu/audio/select_char.ogg");
    sonido->agregarSonido("Menu.move","menu/audio/move.ogg");
    sonido->agregarSonido("Menu.move_char","menu/audio/move_char.ogg");
    sonido->agregarSonido("Menu.back","menu/audio/back.ogg");

    for(TiXmlNode* elemento=doc->FirstChild();
            elemento!=NULL;
            elemento=elemento->NextSibling())
    {
        TiXmlElement* e=elemento->ToElement();
        if(strcmp(e->Value(),"CharSelect")==0)
        {
            char_select=new MenuCharSelect(painter,atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("width")),atoi(e->Attribute("height")),
                                                          atoi(e->Attribute("size_x")),atoi(e->Attribute("size_y")),atoi(e->Attribute("box_size_x")),atoi(e->Attribute("box_size_y")),
                                                          atoi(e->Attribute("box_separation_x")),atoi(e->Attribute("box_separation_y")),
                                                          atoi(e->Attribute("chars_player1")),atoi(e->Attribute("chars_player2")),
                                                          atoi(e->Attribute("preview_player1_x")),atoi(e->Attribute("preview_player1_y")),
                                                          atoi(e->Attribute("preview_player2_x")),atoi(e->Attribute("preview_player2_y")),
                                                          chars,
                                                          atoi(e->Attribute("player1_cursor_x")),atoi(e->Attribute("player1_cursor_y")),
                                                          atoi(e->Attribute("player2_cursor_x")),atoi(e->Attribute("player2_cursor_y"))
                                                          );
            elementos.push_back((Elemento*)char_select);
        }else if(strcmp(e->Value(),"Image")==0)
        {
            std::string path(e->Attribute("path"));
            std::string dir("menu/");
            path=dir+path;
            int displacement_x=0;
            int displacement_y=0;
            int stop_displacement_x_at=0;
            int stop_displacement_y_at=0;
            int fade_in_initial=-1;
            int fade_in_speed=0;
            if(e->Attribute("displacement_x")!=NULL)
                displacement_x=atoi(e->Attribute("displacement_x"));
            if(e->Attribute("displacement_y")!=NULL)
                displacement_y=atoi(e->Attribute("displacement_y"));
            if(e->Attribute("stop_displacement_x_at")!=NULL)
                stop_displacement_x_at=atoi(e->Attribute("stop_displacement_x_at"));
            if(e->Attribute("stop_displacement_y_at")!=NULL)
                stop_displacement_y_at=atoi(e->Attribute("stop_displacement_y_at"));
            if(e->Attribute("fade_in_initial")!=NULL)
                fade_in_initial=atoi(e->Attribute("fade_in_initial"));
            if(e->Attribute("fade_in_speed")!=NULL)
                fade_in_speed=atoi(e->Attribute("fade_in_speed"));

            Image* image=painter->getTexture(path);

            elementos.push_back((Elemento*)new MenuImagen(painter,atoi(e->Attribute("x")),atoi(e->Attribute("y")),displacement_x,displacement_y,stop_displacement_x_at,stop_displacement_y_at,fade_in_initial,fade_in_speed,
                                                          atoi(e->Attribute("width")),atoi(e->Attribute("height")),strcmp(e->Attribute("visible"),"true")==0,image,""
                                                          ));
        }else if(strcmp(e->Value(),"Text")==0)
        {
                elementos.push_back((Elemento*)new MenuTexto(painter,atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("width")),atoi(e->Attribute("height")),strcmp(e->Attribute("visible"),"true")==0,
                                                             e->Attribute("text")
                                                             ));
        }else if(strcmp(e->Value(),"Container")==0)
        {
            std::vector<Elemento*>elementos_contenedor;
            for(TiXmlNode* elem_container=elemento->FirstChild();
                    elem_container!=NULL;
                    elem_container=elem_container->NextSibling())
            {
                TiXmlElement* ec=elem_container->ToElement();
                if(strcmp(ec->Value(),"Button")==0)
                {
                    int action=-1;
                    if(strcmp(ec->Attribute("action"),"1v1")==0)
                        action=0;
                    if(strcmp(ec->Attribute("action"),"PvCPU")==0)
                        action=1;
                    if(strcmp(ec->Attribute("action"),"Continue")==0)
                        action=2;
                    if(strcmp(ec->Attribute("action"),"Exit")==0)
                        action=3;
                    if(strcmp(ec->Attribute("action"),"Load")==0)
                        action=4;
                    if(strcmp(ec->Attribute("action"),"Training")==0)
                        action=5;
                    if(strcmp(ec->Attribute("action"),"2v2")==0)
                        action=6;
                    if(strcmp(ec->Attribute("action"),"3v3")==0)
                        action=7;
                    if(strcmp(ec->Attribute("action"),"Save Config")==0)
                        action=8;


                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:up")==0)
                        action=10;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:down")==0)
                        action=11;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:left")==0)
                        action=12;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:right")==0)
                        action=13;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:a")==0)
                        action=14;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:b")==0)
                        action=15;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:c")==0)
                        action=16;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:d")==0)
                        action=17;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:e")==0)
                        action=18;
                    if(strcmp(ec->Attribute("action"),"Player1.KeyConfig:f")==0)
                        action=19;

                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:up")==0)
                        action=20;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:down")==0)
                        action=21;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:left")==0)
                        action=22;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:right")==0)
                        action=23;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:a")==0)
                        action=24;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:b")==0)
                        action=25;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:c")==0)
                        action=26;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:d")==0)
                        action=27;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:e")==0)
                        action=28;
                    if(strcmp(ec->Attribute("action"),"Player2.KeyConfig:f")==0)
                        action=29;

                    char* menu_load=new char[255];
                    strcpy(menu_load,"");
                    if(action==4)
                    {
                        strcpy(menu_load,"menu/");
                        strcat(menu_load,ec->Attribute("load_menu"));
                    }

                    elementos_contenedor.push_back((Elemento*)new MenuBoton(painter,atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("width")),atoi(ec->Attribute("height")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path"))),atoi(ec->Attribute("text_x")),atoi(ec->Attribute("text_y")),ec->Attribute("text"),
                                                                            painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_selected"))),atoi(ec->Attribute("text_x_selected")),atoi(ec->Attribute("text_y_selected")),ec->Attribute("text_selected"),
                                                                            action,menu_load
                                                                            ));
                }
                if(strcmp(ec->Value(),"Bar")==0)
                {
                    int accion=-1;
                    int default_value=atoi(ec->Attribute("default_value"));
                    if(ec->Attribute("action")!=NULL)
                    {
                        if(strcmp(ec->Attribute("action"),"AI level")==0)
                        {
                            accion=0;
                            default_value=ai_level;
                        }
                    }
                        accion=atoi(ec->Attribute("action"));
                    elementos_contenedor.push_back((Elemento*)new MenuBarra(painter,atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("width")),atoi(ec->Attribute("height")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_bg"))),atoi(ec->Attribute("bar_x")),atoi(ec->Attribute("bar_y")),painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path"))),
                                                                            painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_bg_selected"))),atoi(ec->Attribute("bar_x_selected")),atoi(ec->Attribute("bar_y_selected")),painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_selected"))),
                                                                            atoi(ec->Attribute("max")),default_value,accion
                                                                            )
                                                   );
                }
                if(strcmp(ec->Value(),"List")==0)
                {
                    std::vector<Elemento*>elem_lista;

                    for(TiXmlNode* elem_list=elem_container->FirstChild();
                            elem_list!=NULL;
                            elem_list=elem_list->NextSibling())
                    {
                        TiXmlElement* el=elem_list->ToElement();
                        if(strcmp(el->Value(),"Text")==0)
                            elem_lista.push_back((Elemento*)new MenuTexto(painter,atoi(ec->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("width")),atoi(el->Attribute("height")),strcmp(el->Attribute("visible"),"true")==0,
                                                             el->Attribute("text")
                                                             ));
                        if(strcmp(el->Value(),"Image")==0)
                        {
                            std::string path(el->Attribute("path"));
                            std::string dir("menu/");
                            path=dir+path;

                            int displacement_x=0;
                            int displacement_y=0;
                            int stop_displacement_x_at=0;
                            int stop_displacement_y_at=0;
                            int fade_in_initial=-1;
                            int fade_in_speed=0;
                            if(e->Attribute("displacement_x")!=NULL)
                                displacement_x=atoi(e->Attribute("displacement_x"));
                            if(e->Attribute("displacement_y")!=NULL)
                                displacement_y=atoi(e->Attribute("displacement_y"));
                            if(e->Attribute("stop_displacement_x_at")!=NULL)
                                stop_displacement_x_at=atoi(e->Attribute("stop_displacement_x_at"));
                            if(e->Attribute("stop_displacement_y_at")!=NULL)
                                stop_displacement_y_at=atoi(e->Attribute("stop_displacement_y_at"));
                            if(e->Attribute("fade_in_initial")!=NULL)
                                fade_in_initial=atoi(e->Attribute("fade_in_initial"));
                            if(e->Attribute("fade_in_speed")!=NULL)
                                fade_in_speed=atoi(e->Attribute("fade_in_speed"));

                            Image*image=painter->getTexture(path);

//                            if(fade_in_initial!=-1)//!!SET APLHA
//                                painter->setAlpha(fade_in_initial,image,original_image);

                            elem_lista.push_back((Elemento*)new MenuImagen(painter,atoi(el->Attribute("x")),atoi(el->Attribute("y")),displacement_x,displacement_y,stop_displacement_x_at,stop_displacement_y_at,fade_in_initial,fade_in_speed,
                                                                           atoi(el->Attribute("width")),atoi(el->Attribute("height")),strcmp(el->Attribute("visible"),"true")==0,image,""
                                                                           ));
                        }
                        if(strcmp(el->Value(),"chars")==0)
                        {
//                            int player=atoi(el->Attribute("player"));
//                            int pos=atoi(el->Attribute("number"));
//                            if(player==1)
//                                pos_pa[pos]=elementos_contenedor.size();
//                            if(player==2)
//                                pos_pb[pos]=elementos_contenedor.size();
                            for(int i=0;i<(int)chars.size();i++)
                            elem_lista.push_back((Elemento*)new MenuTexto(painter,atoi(el->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("width")),atoi(el->Attribute("height")),strcmp(el->Attribute("visible"),"true")==0,
                                                             chars[i]
                                                             ));
                        }
                        if(strcmp(el->Value(),"stage")==0)
                        {
                            pos_stage=elementos_contenedor.size();
                            for(int i=0;i<(int)stages.size();i++)
                            {
                                int displacement_x=0;
                                int displacement_y=0;
                                int stop_displacement_x_at=0;
                                int stop_displacement_y_at=0;
                                int fade_in_initial=-1;
                                int fade_in_speed=0;
                                if(e->Attribute("displacement_x")!=NULL)
                                    displacement_x=atoi(e->Attribute("displacement_x"));
                                if(e->Attribute("displacement_y")!=NULL)
                                    displacement_y=atoi(e->Attribute("displacement_y"));
                                if(e->Attribute("stop_displacement_x_at")!=NULL)
                                    stop_displacement_x_at=atoi(e->Attribute("stop_displacement_x_at"));
                                if(e->Attribute("stop_displacement_y_at")!=NULL)
                                    stop_displacement_y_at=atoi(e->Attribute("stop_displacement_y_at"));
                                if(e->Attribute("fade_in_initial")!=NULL)
                                    fade_in_initial=atoi(e->Attribute("fade_in_initial"));
                                if(e->Attribute("fade_in_speed")!=NULL)
                                    fade_in_speed=atoi(e->Attribute("fade_in_speed"));

                                Image*image=painter->getTexture(std::string("stages/")+stages[i]+std::string("/images/preview.png"));


                                elem_lista.push_back((Elemento*)new MenuImagen(painter,atoi(el->Attribute("x")),atoi(el->Attribute("y")),displacement_x,displacement_y,stop_displacement_x_at,stop_displacement_y_at,fade_in_initial,fade_in_speed,
                                                                               atoi(el->Attribute("width")),atoi(el->Attribute("height")),strcmp(el->Attribute("visible"),"true")==0,image,stages[i]
                                                                               ));
                            }
//                            elem_lista.push_back((Elemento*)new MenuTexto(painter,atoi(el->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("width")),atoi(el->Attribute("height")),strcmp(el->Attribute("visible"),"true")==0,
//                                                             stages[i],video::SColor(atoi(el->Attribute("alpha")),atoi(el->Attribute("red")),atoi(el->Attribute("green")),atoi(el->Attribute("blue")))
//                                                             ));
                        }
                    }
                    int accion=-1;
                    if(ec->Attribute("action")!=NULL)
                    {
//                        if(strcmp(ec->Attribute("action"),"Time")==0)
//                            accion=0;
//                        if(strcmp(ec->Attribute("action"),"Rounds")==0)
//                            accion=1;

                        if(strcmp(ec->Attribute("action"),"1v1")==0)
                            accion=0;
                        if(strcmp(ec->Attribute("action"),"2v2")==0)
                            accion=1;
                        if(strcmp(ec->Attribute("action"),"3v3")==0)
                            accion=3;

                        if(strcmp(ec->Attribute("action"),"1v1cpu")==0)
                            accion=4;
                        if(strcmp(ec->Attribute("action"),"2v2cpu")==0)
                            accion=5;
                        if(strcmp(ec->Attribute("action"),"3v3cpu")==0)
                            accion=6;
                    }
                    elementos_contenedor.push_back((Elemento*)new MenuLista(painter,atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("width")),atoi(ec->Attribute("height")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            atoi(ec->Attribute("arrow_left_x")),atoi(ec->Attribute("arrow_left_y")),painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_left"))),
                                                                            atoi(ec->Attribute("arrow_right_x")),atoi(ec->Attribute("arrow_right_y")),painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_right"))),
                                                                            atoi(ec->Attribute("arrow_left_x_selected")),atoi(ec->Attribute("arrow_left_y_selected")),painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_left_selected"))),
                                                                            atoi(ec->Attribute("arrow_right_x_selected")),atoi(ec->Attribute("arrow_right_y_selected")),painter->getTexture(std::string("menu/")+std::string(ec->Attribute("path_right_selected"))),
                                                                            elem_lista,
                                                                            accion
                                                                            )
                                                   );
                }
            }
            contenedor_actual=new MenuContenedor(painter,atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("width")),atoi(e->Attribute("height")),strcmp(e->Attribute("visible"),"true")
                                                              ,elementos_contenedor);
            elementos.push_back((Elemento*)contenedor_actual);
        }
    }
}

Personaje* Menu::getPersonajeA(int num,bool ia)
{
    writeLogLine("Initializing player's 1 character #"+painter->convertInt(num)+".");
    //get string
    std::string char_name=char_select->getLockedNamesPA()[num];
    int num_paleta=char_select->getLockedPalettesPA()[num];

    //get cadena
    char *path_a=new char[255];
    strcpy(path_a,"");
    strcat(path_a,char_name.c_str());

    if(ia)
    {
        writeLogLine("Loading AI.");
        inputa=new Input();
        char*file_ia=new char[255];
        strcpy(file_ia,"chars/");
        strcat(file_ia,path_a);
        strcat(file_ia,"/ia.xml");
        inputa->cargarIAXML(2,file_ia,"");
    }else
    {
        writeLogLine("Loading inputs.");
        inputa=new Input();
        inputa->cargarDesdeXML(1,receiver);
    }

    //get char
    Personaje* p=new Personaje(painter,sonido,1,num_paleta);
    p->cargarDesdeXML(stage->size/2-painter->screen_width/4-200,0,inputa,(char *)path_a);
    writeLogLine("Loaded successfully.");
    return p;
}

Personaje* Menu::getPersonajeB(int num,bool ia)
{
    writeLogLine("Initializing player's 1 character #"+painter->convertInt(num)+".");
    //get string
    std::string char_name=char_select->getLockedNamesPB()[num];
    int num_paleta=char_select->getLockedPalettesPB()[num];

    //get string
    char *path_b=new char[255];
    strcpy(path_b,"");
    strcat(path_b,char_name.c_str());

    if(ia)
    {
        writeLogLine("Loading AI.");
        inputb=new Input();
        char*file_ia=new char[255];
        char*file_ia_default=new char[255];
        strcpy(file_ia,"chars/");
        strcpy(file_ia_default,"chars/");
        strcat(file_ia,path_b);
        strcat(file_ia_default,path_b);
        strcat(file_ia_default,"/ai/default.xml");
        if(ai_level==1)
            strcat(file_ia,"/ai/level 1.xml");
        if(ai_level==2)
            strcat(file_ia,"/ai/level 2.xml");
        if(ai_level==3)
            strcat(file_ia,"/ai/level 3.xml");
        if(ai_level==4)
            strcat(file_ia,"/ai/level 4.xml");
        if(ai_level==5)
            strcat(file_ia,"/ai/level 5.xml");
        inputb->cargarIAXML(2,file_ia,file_ia_default);
    }else
    {
        writeLogLine("Loading inputs.");
        inputb=new Input();
        inputb->cargarDesdeXML(2,receiver);
    }

    //get char
    Personaje* p=new Personaje(painter,sonido,2,num_paleta);
    p->cargarDesdeXML(stage->size/2-painter->screen_width/4+200,0,inputb,(char *)path_b);
    writeLogLine("Loaded successfully.");
    return p;
}

std::string Menu::getStage()
{
    //!
    MenuContenedor *mc=((MenuContenedor*)contenedor_actual);
    MenuLista *ml=(MenuLista*)mc->elementos[pos_stage];
    MenuImagen *mt=(MenuImagen*)ml->getElementoActual();
    std::string str=mt->value;

    return str;
}

bool Menu::getExitSignal()
{
    bool temp=exit_signal;
    exit_signal=false;
    return temp;
}

bool Menu::getSaveInputsSignal()
{
    bool temp=save_inputs_signal;
    save_inputs_signal=false;
    return temp;
}

void Menu::escribirInputsXML(Input* ia,Input* ib)
{
    TiXmlDocument *doc=new TiXmlDocument();
    ib->getXML(ia->getXML(doc));
    doc->SaveFile( "misc/inputs.xml" );
}

std::string Menu::getInputPressed()
{
    while(true)
    {

        dibujarMenu();
        if(receiver->IsKeyDownn(irr::KEY_KEY_Q))
            return "Q";
        if(receiver->IsKeyDownn(SDLK_w))
            return "W";
        if(receiver->IsKeyDownn(irr::KEY_KEY_E))
            return "E";
        if(receiver->IsKeyDownn(irr::KEY_KEY_R))
            return "R";
        if(receiver->IsKeyDownn(irr::KEY_KEY_T))
            return "T";
        if(receiver->IsKeyDownn(irr::KEY_KEY_Y))
            return "Y";
        if(receiver->IsKeyDownn(irr::KEY_KEY_U))
            return "U";
        if(receiver->IsKeyDownn(irr::KEY_KEY_I))
            return "I";
        if(receiver->IsKeyDownn(irr::KEY_KEY_O))
            return "O";
        if(receiver->IsKeyDownn(irr::KEY_KEY_P))
            return "P";
        if(receiver->IsKeyDownn(irr::KEY_KEY_A))
            return "A";
        if(receiver->IsKeyDownn(irr::KEY_KEY_S))
            return "S";
        if(receiver->IsKeyDownn(irr::KEY_KEY_D))
            return "D";
        if(receiver->IsKeyDownn(irr::KEY_KEY_F))
            return "F";
        if(receiver->IsKeyDownn(irr::KEY_KEY_G))
            return "G";
        if(receiver->IsKeyDownn(irr::KEY_KEY_H))
            return "H";
        if(receiver->IsKeyDownn(irr::KEY_KEY_J))
            return "J";
        if(receiver->IsKeyDownn(irr::KEY_KEY_K))
            return "K";
        if(receiver->IsKeyDownn(irr::KEY_KEY_L))
            return "L";
        if(receiver->IsKeyDownn(irr::KEY_KEY_Z))
            return "Z";
        if(receiver->IsKeyDownn(irr::KEY_KEY_X))
            return "X";
        if(receiver->IsKeyDownn(irr::KEY_KEY_C))
            return "C";
        if(receiver->IsKeyDownn(irr::KEY_KEY_V))
            return "V";
        if(receiver->IsKeyDownn(irr::KEY_KEY_B))
            return "B";
        if(receiver->IsKeyDownn(irr::KEY_KEY_N))
            return "N";
        if(receiver->IsKeyDownn(irr::KEY_KEY_M))
            return "M";

        if(receiver->IsJoyDown(0,0))
            return "j0-0";
        if(receiver->IsJoyDown(1,0))
            return "j0-1";
        if(receiver->IsJoyDown(2,0))
            return "j0-2";
        if(receiver->IsJoyDown(3,0))
            return "j0-3";
        if(receiver->IsJoyDown(4,0))
            return "j0-4";
        if(receiver->IsJoyDown(5,0))
            return "j0-5";
        if(receiver->IsJoyDown(6,0))
            return "j0-6";
        if(receiver->IsJoyDown(7,0))
            return "j0-7";
        if(receiver->IsJoyDown(8,0))
            return "j0-8";
        if(receiver->IsJoyDown(9,0))
            return "j0-9";
        if(receiver->IsJoyDown(10,0))
            return "j0-10";
        if(receiver->IsJoyDown(-2,0))
            return "j0-d";
        if(receiver->IsJoyDown(-4,0))
            return "j0-l";
        if(receiver->IsJoyDown(-6,0))
            return "j0-r";
        if(receiver->IsJoyDown(-8,0))
            return "j0-u";

        if(receiver->IsJoyDown(0,1))
            return "j1-0";
        if(receiver->IsJoyDown(1,1))
            return "j1-1";
        if(receiver->IsJoyDown(2,1))
            return "j1-2";
        if(receiver->IsJoyDown(3,1))
            return "j1-3";
        if(receiver->IsJoyDown(4,1))
            return "j1-4";
        if(receiver->IsJoyDown(5,1))
            return "j1-5";
        if(receiver->IsJoyDown(6,1))
            return "j1-6";
        if(receiver->IsJoyDown(7,1))
            return "j1-7";
        if(receiver->IsJoyDown(8,1))
            return "j1-8";
        if(receiver->IsJoyDown(9,1))
            return "j1-9";
        if(receiver->IsJoyDown(10,1))
            return "j1-10";
        if(receiver->IsJoyDown(-2,1))
            return "j1-d";
        if(receiver->IsJoyDown(-4,1))
            return "j1-l";
        if(receiver->IsJoyDown(-6,1))
            return "j1-r";
        if(receiver->IsJoyDown(-8,1))
            return "j1-u";
    }
}

int Menu::toKeyCode(std::string str)
{
    if(str==std::string("Q"))
        return irr::KEY_KEY_Q;
    if(str==std::string("W"))
        return SDLK_w;
    if(str==std::string("E"))
        return irr::KEY_KEY_E;
    if(str==std::string("R"))
        return irr::KEY_KEY_R;
    if(str==std::string("T"))
        return irr::KEY_KEY_T;
    if(str==std::string("Y"))
        return irr::KEY_KEY_Y;
    if(str==std::string("U"))
        return irr::KEY_KEY_U;
    if(str==std::string("I"))
        return irr::KEY_KEY_I;
    if(str==std::string("O"))
        return irr::KEY_KEY_O;
    if(str==std::string("P"))
        return irr::KEY_KEY_P;
    if(str==std::string("A"))
        return irr::KEY_KEY_A;
    if(str==std::string("S"))
        return irr::KEY_KEY_S;
    if(str==std::string("D"))
        return irr::KEY_KEY_D;
    if(str==std::string("F"))
        return irr::KEY_KEY_F;
    if(str==std::string("G"))
        return irr::KEY_KEY_G;
    if(str==std::string("H"))
        return irr::KEY_KEY_H;
    if(str==std::string("J"))
        return irr::KEY_KEY_J;
    if(str==std::string("K"))
        return irr::KEY_KEY_K;
    if(str==std::string("L"))
        return irr::KEY_KEY_L;
    if(str==std::string("Z"))
        return irr::KEY_KEY_Z;
    if(str==std::string("X"))
        return irr::KEY_KEY_X;
    if(str==std::string("C"))
        return irr::KEY_KEY_C;
    if(str==std::string("V"))
        return irr::KEY_KEY_V;
    if(str==std::string("B"))
        return irr::KEY_KEY_B;
    if(str==std::string("N"))
        return irr::KEY_KEY_N;
    if(str==std::string("M"))
        return irr::KEY_KEY_M;
    return irr::KEY_ESCAPE;
}


void Menu::llenarInputsBotones()
{
    for(int i=0;i<(int)contenedor_actual->elementos.size();i++)
    {
        if(((MenuContenedor*)contenedor_actual)->elementos[i]->getTipo()==4)
        {
            MenuBoton*mb=(MenuBoton*)contenedor_actual->elementos[i];
            if(mb->getAccion()>=10 && mb->getAccion()<=29)
            {
                int player;
                std::string mapeo="";
                int accion=mb->getAccion();
                if(accion>=10 && accion<=19)
                    player=1;
                else
                    player=2;
                Input* temp=new Input();
                Input* temp2=new Input();
                if(player==1)
                {
                    temp->cargarDesdeXML(1,receiver);
                    temp2->cargarDesdeXML(2,receiver);
                }else
                {
                    temp->cargarDesdeXML(2,receiver);
                    temp2->cargarDesdeXML(1,receiver);
                }
                if(accion==10||accion==20)mapeo="8";
                if(accion==11||accion==21)mapeo="2";
                if(accion==12||accion==22)mapeo="4";
                if(accion==13||accion==23)mapeo="6";
                if(accion==14||accion==24)mapeo="a";
                if(accion==15||accion==25)mapeo="b";
                if(accion==16||accion==26)mapeo="c";
                if(accion==17||accion==27)mapeo="d";
                if(accion==18||accion==28)mapeo="e";
                if(accion==19||accion==29)mapeo="f";

                //key
                mb->input_config="";
                int pos=-1,posc=-1;
                for(int j=0;j<(int)temp->botones.size();j++)
                    if(temp->botones[j].getMapeo()==mapeo && !temp->botones[j].usaJoystick())
                        pos=j;

                for(int j=0;j<(int)temp->cruz.size();j++)
                    if(temp->cruz[j].getMapeo()==mapeo && !temp->cruz[j].usaJoystick())
                        posc=j;

                if(pos!=-1)
                    mb->input_config=temp->botones[pos].keyToString();

                if(posc!=-1)
                    mb->input_config=temp->cruz[posc].keyToString();

                //joy
                pos=-1;
                for(int j=0;j<(int)temp->botones.size();j++)
                    if(temp->botones[j].getMapeo()==mapeo && temp->botones[j].usaJoystick())
                        pos=j;
                posc=-1;
                for(int j=0;j<(int)temp->cruz.size();j++)
                    if(temp->cruz[j].getMapeo()==mapeo && temp->cruz[j].usaJoystick())
                        posc=j;

                if(pos!=-1)
                {
                    mb->input_config+=" j";
                    mb->input_config+=painter->convertInt((int)temp->botones[pos].getNumJoystick());
                    mb->input_config+=painter->convertInt((int)temp->botones[pos].joystick);
                }

                if(posc!=-1)
                {
                    mb->input_config+=" j";
                    mb->input_config+=painter->convertInt((int)temp->cruz[posc].getNumJoystick());
                    mb->input_config+="-";
                    if(temp->cruz[posc].joystick==-8)
                        mb->input_config+=std::string("up");
                    else if(temp->cruz[posc].joystick==-2)
                        mb->input_config+=std::string("down");
                    else if(temp->cruz[posc].joystick==-4)
                        mb->input_config+=std::string("left");
                    else if(temp->cruz[posc].joystick==-6)
                        mb->input_config+=std::string("right");
                    else
                        mb->input_config+=painter->convertInt((int)temp->cruz[posc].joystick);
                }
            }
        }
    }
}

void Menu::printVsScreen(vector<Image*>pa_previews,vector<Image*>pb_previews)
{
    painter->draw2DImage
    (   vs_screen,
        vs_screen->getWidth(),vs_screen->getHeight(),
        0,0,
        1.0,
        false,
        0,0,
        Color(255,255,255,255),
        false);

    for(int i=0;i<(int)pa_previews.size();i++)
    {
        Image*texture=pa_previews[i];
        painter->draw2DImage
        (   texture,
            texture->getWidth(),texture->getHeight(),
            i*200,painter->screen_height-texture->getHeight()-150,
            1.0,
            false,
            0,0,
            Color(255,255,255,255),
            false);
    }

    for(int i=0;i<(int)pb_previews.size();i++)
    {
        Image*texture=pb_previews[i];
        painter->draw2DImage
        (   texture,
            texture->getWidth(),texture->getHeight(),
            painter->screen_width-(i+1)*texture->getWidth()-50,painter->screen_height-texture->getHeight()-150,
            1.0,
            false,
            0,0,
            Color(255,255,255,255),
            false);
    }
    painter->updateScreen();
}
