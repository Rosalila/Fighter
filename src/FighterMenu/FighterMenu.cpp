#include "FighterMenu/FighterMenu.h"
Menu::Menu(Painter* painter,Receiver* receiver,Sound* sonido,char* archivo)
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
            break;
        }

        for(int i=0;i<num_personajes;i++)
        {
            Personaje* p1a=pa[i];
            Personaje* p1b=pb[i];
            p1a->resetPersonaje();
            p1b->resetPersonaje();
        }
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
            if(e->getTipo()=="Imagen")//Is MenuImagen
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
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p1_x++;
                if(char_select->select_p1_x>=char_select->size_x)
                    char_select->select_p1_x=0;
                tecla_arriba_p1=false;
            }else if(inputa->getBufferInputs()[0]=="4")
            {
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p1_x--;
                if(char_select->select_p1_x<0)
                    char_select->select_p1_x=char_select->size_x-1;
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="2")
            {
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p1_y++;
                if(char_select->select_p1_y>=char_select->size_y)
                    char_select->select_p1_y=0;
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="8")
            {
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p1_y--;
                if(char_select->select_p1_y<0)
                    char_select->select_p1_y=char_select->size_y-1;
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="a")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPA(0);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="b")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPA(1);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="c")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPA(2);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="d")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPA(3);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="e")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPA(4);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="f")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPA(5);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="g")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPA(6);
                tecla_arriba_p1=false;
            }
            else if(inputa->getBufferInputs()[0]=="h")
            {
                sonido->playSound(std::string("Menu.select_char"));
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
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p2_x++;
                if(char_select->select_p2_x>=char_select->size_x)
                    char_select->select_p2_x=0;
                tecla_arriba_p2=false;
            }else if(inputb->getBufferInputs()[0]=="4")
            {
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p2_x--;
                if(char_select->select_p2_x<0)
                    char_select->select_p2_x=char_select->size_x-1;
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="2")
            {
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p2_y++;
                if(char_select->select_p2_y>=char_select->size_y)
                    char_select->select_p2_y=0;
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="8")
            {
                sonido->playSound(std::string("Menu.move_char"));
                char_select->select_p2_y--;
                if(char_select->select_p2_y<0)
                    char_select->select_p2_y=char_select->size_y-1;
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="a")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPB(0);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="b")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPB(1);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="c")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPB(2);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="d")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPB(3);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="e")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPB(4);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="f")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPB(5);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="g")
            {
                sonido->playSound(std::string("Menu.select_char"));
                char_select->lockPB(6);
                tecla_arriba_p2=false;
            }
            else if(inputb->getBufferInputs()[0]=="h")
            {
                sonido->playSound(std::string("Menu.select_char"));
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
            if(receiver->IsKeyDownn(SDLK_g))
            {
                painter->explode();
            }

            tecla_arriba=false;
            if(receiver->IsKeyDownn(SDLK_ESCAPE))
            {
                sonido->playSound(std::string("Menu.back"));
                exit_signal=true;
                break;
            }
            else if(receiver->IsKeyDownn(SDLK_DOWN))
            {
                sonido->playSound(std::string("Menu.move"));
                ((MenuContenedor*)selectables_container)->avanzar();
            }
            else if(receiver->IsKeyDownn(SDLK_UP))
            {
                sonido->playSound(std::string("Menu.move"));
                ((MenuContenedor*)selectables_container)->retroceder();
            }
            else if(receiver->IsKeyDownn(SDLK_RIGHT))
            {
                sonido->playSound(std::string("Menu.move"));
                if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Lista")
                {
                    MenuLista* ml=((MenuLista*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
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
                if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Barra")
                {
                    MenuBarra* mb=((MenuBarra*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                    mb->avanzar();
                    if(mb->getAccion()==0)
                    {
                        ai_level=mb->actual;
                    }
                }
            }
            else if(receiver->IsKeyDownn(SDLK_LEFT))
            {
                sonido->playSound(std::string("Menu.move"));
                if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Lista")
                {
                    MenuLista* ml=((MenuLista*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
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
                if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Barra")
                {
                    MenuBarra* mb=((MenuBarra*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                    mb->retroceder();
                    if(mb->getAccion()==0)
                    {
                        ai_level=mb->actual;
                    }
                }
            }else if(receiver->IsKeyPressed(SDLK_RETURN))
            {
                sonido->playSound(std::string("Menu.select"));
                if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Lista")
                {
                    MenuLista*ml=((MenuLista*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                    if(ml->getAccion()=="1v1")
                        if(char_select->listo())
                            iniciarJuego(1,false);
                    if(ml->getAccion()=="2v2")
                        if(char_select->listo())
                            iniciarJuego(2,false);
                    if(ml->getAccion()=="3v3")
                        if(char_select->listo())
                            iniciarJuego(3,false);
                    if(ml->getAccion()=="1v1cpu")
                        if(char_select->listoPA())
                            iniciarJuego(1,true);
                    if(ml->getAccion()=="2v2cpu")
                        if(char_select->listoPA())
                            iniciarJuego(2,true);
                    if(ml->getAccion()=="3v3cpu")
                        if(char_select->listoPA())
                            iniciarJuego(3,true);
                }
                if(((MenuContenedor*)selectables_container)->getElementoSeleccionado()->getTipo()=="Boton")
                {
                    MenuBoton*mb=((MenuBoton*)((MenuContenedor*)selectables_container)->getElementoSeleccionado());
                    if(mb->getAccion()=="exit")
                    {
                        break;
                    }
                    if(mb->getAccion()=="quit")
                    {
                        exit_signal=true;
                        break;
                    }
                    if(mb->getAccion()=="load")
                    {
                        Menu *temp=new Menu(painter,receiver,sonido,mb->load_menu);
                        temp->loopMenu();
                    }
                    if(mb->getAccion()=="training")
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
                    if(mb->getAccion()=="save config")//save config
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
//                    if(mb->getAccion()>=10 && mb->getAccion()<=29)
//                    {
//                        int player;
//                        std::string mapeo="";
//                        int accion=mb->getAccion();
//                        if(accion>=10 && accion<=19)
//                            player=1;
//                        else
//                            player=2;
//                        Input* temp=new Input();
//                        Input* temp2=new Input();
//                        if(player==1)
//                        {
//                            temp->cargarDesdeXML(1,receiver);
//                            temp2->cargarDesdeXML(2,receiver);
//                        }else
//                        {
//                            temp->cargarDesdeXML(2,receiver);
//                            temp2->cargarDesdeXML(1,receiver);
//                        }
//                        if(accion==10||accion==20)mapeo="8";
//                        if(accion==11||accion==21)mapeo="2";
//                        if(accion==12||accion==22)mapeo="4";
//                        if(accion==13||accion==23)mapeo="6";
//                        if(accion==14||accion==24)mapeo="a";
//                        if(accion==15||accion==25)mapeo="b";
//                        if(accion==16||accion==26)mapeo="c";
//                        if(accion==17||accion==27)mapeo="d";
//                        if(accion==18||accion==28)mapeo="e";
//                        if(accion==19||accion==29)mapeo="f";
//
//                        mb->input_config="";
//                        std::string str_input=getInputPressed();
//                        //key
//                        if((char)str_input[0]!='j')
//                        {
//                            int pos=-1,posc=-1;
//                            for(int j=0;j<(int)temp->botones.size();j++)
//                                if(temp->botones[j].getMapeo()==mapeo && !temp->botones[j].usaJoystick())
//                                    pos=j;
//
//                            for(int j=0;j<(int)temp->cruz.size();j++)
//                                if(temp->cruz[j].getMapeo()==mapeo && !temp->cruz[j].usaJoystick())
//                                    posc=j;
//
//                            Boton b(receiver,toKeyCode(str_input),mapeo);
//                            if(pos!=-1)
//                                temp->botones[pos]=b;
//                            else if (posc!=-1)
//                                temp->cruz[posc]=b;
//                            else
//                                temp->botones.push_back(b);
//                        }else//joy
//                        {
//                            int pos=-1,posc=-1;
//                            for(int j=0;j<(int)temp->botones.size();j++)
//                                if(temp->botones[j].getMapeo()==mapeo && temp->botones[j].usaJoystick())
//                                    pos=j;
//
//                            for(int j=0;j<(int)temp->cruz.size();j++)
//                                if(temp->cruz[j].getMapeo()==mapeo && temp->cruz[j].usaJoystick())
//                                    posc=j;
//
//                            int int_input=((int)(str_input[3]))-48;
//                            if((char)str_input[3]=='u')
//                                int_input=-8;
//                            if((char)str_input[3]=='d')
//                                int_input=-2;
//                            if((char)str_input[3]=='l')
//                                int_input=-4;
//                            if((char)str_input[3]=='r')
//                                int_input=-6;
//                            Boton b(receiver,int_input,((int)str_input[1])-48,mapeo);
//                            if(pos!=-1)
//                            {
//                                temp->botones[pos]=b;
//                            }else if(posc!=-1)
//                            {
//                                temp->cruz[posc]=b;
//                            }else
//                            {
//                                temp->botones.push_back(b);
//                            }
//                        }
//
//                        escribirInputsXML(temp,temp2);
//                        //mb->input_config=b.keyToString();
//                        llenarInputsBotones();
//                    }
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

    painter->draw3D(200,200);

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

    sonido->addSound("Menu.select","menu/audio/select.ogg");
    sonido->addSound("Menu.select_char","menu/audio/select_char.ogg");
    sonido->addSound("Menu.move","menu/audio/move.ogg");
    sonido->addSound("Menu.move_char","menu/audio/move_char.ogg");
    sonido->addSound("Menu.back","menu/audio/back.ogg");

    TiXmlNode* elemento=doc->FirstChild("svg");
    TiXmlNode* g_node=elemento->FirstChild("g");

    std::vector<Elemento*>elementos_contenedor;
    for(TiXmlNode* image_node=g_node->FirstChild("image");
            image_node!=NULL;
            image_node=image_node->NextSibling("image"))
    {
        TiXmlElement* e=image_node->ToElement();

        if(e->Attribute("type")==NULL)
        {
            std::string path(e->Attribute("xlink:href"));

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
                                                          atoi(e->Attribute("width")),atoi(e->Attribute("height")),image,""
                                                          ));
        }else if(strcmp(e->Attribute("type"),"button")==0)
        {
            std::string action="";
            if(e->Attribute("action")!=NULL)
               action=e->Attribute("action");

            char* menu_load=new char[255];
            strcpy(menu_load,"");
            if(action=="load")
            {
                strcpy(menu_load,"menu/");
                strcat(menu_load,e->Attribute("load_menu"));
            }

            int x=atoi(e->Attribute("x"));
            int y=atoi(e->Attribute("y"));
            int width=atoi(e->Attribute("width"));
            int height=atoi(e->Attribute("height"));
            std::string path=e->Attribute("xlink:href");

            int text_x=x;
            if(e->Attribute("text_x")!=NULL)
                text_x=atoi(e->Attribute("text_x"));

            int text_y=y;
            if(e->Attribute("text_y")!=NULL)
                text_x=atoi(e->Attribute("text_y"));

            std::string text="";
            if(e->Attribute("text")!=NULL)
                text=e->Attribute("text");

            std::string path_selected=path;
            if(e->Attribute("image_selected")!=NULL)
                path_selected=e->Attribute("image_selected");

            int text_x_selected=text_x;
            if(e->Attribute("text_x_selected")!=NULL)
                text_x_selected=atoi(e->Attribute("text_x_selected"));

            int text_y_selected=text_y;
            if(e->Attribute("text_y_selected")!=NULL)
                text_y_selected=atoi(e->Attribute("text_y_selected"));

            std::string text_selected=text;
            if(e->Attribute("text_selected")!=NULL)
                text_selected=e->Attribute("text_selected");


            elementos_contenedor.push_back((Elemento*)new MenuBoton(painter,
                                                                    x,y,
                                                                    width,height,
                                                                    painter->getTexture(std::string("menu/")+path),
                                                                    text_x,text_y,text,
                                                                    painter->getTexture(std::string("menu/")+path_selected),
                                                                    text_x_selected,text_y_selected,text_selected,
                                                                    action,menu_load
                                                                    ));

        }else if(strcmp(e->Attribute("type"),"bar")==0)
        {
            int accion=-1;
            int default_value=0;
            if(e->Attribute("default_value")!=NULL)
                atoi(e->Attribute("default_value"));
            if(e->Attribute("action")!=NULL)
            {
                if(strcmp(e->Attribute("action"),"AI level")==0)
                {
                    accion=0;
                    default_value=ai_level;
                }
                accion=atoi(e->Attribute("action"));
            }

            int x=atoi(e->Attribute("x"));
            int y=atoi(e->Attribute("y"));
            int width=atoi(e->Attribute("width"));
            int height=atoi(e->Attribute("height"));

            std::string path(e->Attribute("xlink:href"));

            std::string background=path;
            if(e->Attribute("background")!=NULL)
                background=e->Attribute("background");

            int bar_x=x;
            if(e->Attribute("bar_x")!=NULL)
                bar_x=atoi(e->Attribute("bar_x"));

            int bar_y=y;
            if(e->Attribute("bar_y")!=NULL)
                bar_y=atoi(e->Attribute("bar_y"));

            std::string background_selected=background;
            if(e->Attribute("background_selected")!=NULL)
                background_selected=e->Attribute("background_selected");

            int bar_x_selected=bar_x;
            if(e->Attribute("bar_x_selected")!=NULL)
                bar_x_selected=atoi(e->Attribute("bar_x_selected"));

            int bar_y_selected=bar_y;
            if(e->Attribute("bar_y_selected")!=NULL)
                bar_y_selected=atoi(e->Attribute("bar_y_selected"));

            std::string image_selected=path;
            if(e->Attribute("image_selected")!=NULL)
                image_selected=e->Attribute("image_selected");

            int max=9999;
            if(e->Attribute("max")!=NULL)
                max=atoi(e->Attribute("max"));

            elementos_contenedor.push_back((Elemento*)new MenuBarra(painter,
                                                                    x,y,
                                                                    width,height,
                                                                    painter->getTexture(std::string("menu/")+background),
                                                                    bar_x,bar_y,
                                                                    painter->getTexture(std::string("menu/")+path),
                                                                    painter->getTexture(std::string("menu/")+background_selected),
                                                                    bar_x_selected,bar_y_selected,
                                                                    painter->getTexture(std::string("menu/")+image_selected),
                                                                    max,default_value,accion
                                                                    )
                                           );
        }
    }

    if(g_node->FirstChild("rect")!=NULL)
    for(TiXmlNode* rect_node=g_node->FirstChild("rect");
            rect_node!=NULL;
            rect_node=rect_node->NextSibling("rect"))
    {
        TiXmlElement* e=rect_node->ToElement();
        if(e->Attribute("type")!=NULL)
        {
            if(strcmp(e->Attribute("type"),"char_select")==0)
            {
                int x=atoi(e->Attribute("x"));
                int y=atoi(e->Attribute("y"));
                int size_x=3;
                if(e->Attribute("size_x")!=NULL)
                    size_x=atoi(e->Attribute("size_x"));

                int size_y=3;
                if(e->Attribute("size_y")!=NULL)
                    size_y=atoi(e->Attribute("size_y"));

                int box_size_x=100;
                if(e->Attribute("box_size_x")!=NULL)
                    box_size_x=atoi(e->Attribute("box_size_x"));

                int box_size_y=100;
                if(e->Attribute("box_size_y")!=NULL)
                    box_size_y=atoi(e->Attribute("box_size_y"));

                int box_separation_x=0;
                if(e->Attribute("box_separation_x")!=NULL)
                    box_separation_x=atoi(e->Attribute("box_separation_x"));

                int box_separation_y=0;
                if(e->Attribute("box_separation_y")!=NULL)
                    box_separation_y=atoi(e->Attribute("box_separation_y"));

                int chars_player1=1;
                if(e->Attribute("chars_player1")!=NULL)
                    chars_player1=atoi(e->Attribute("chars_player1"));

                int chars_player2=1;
                if(e->Attribute("chars_player2")!=NULL)
                    chars_player2=atoi(e->Attribute("chars_player2"));

                int preview_player1_x=0;
                if(e->Attribute("preview_player1_x")!=NULL)
                    preview_player1_x=atoi(e->Attribute("preview_player1_x"));

                int preview_player1_y=0;
                if(e->Attribute("preview_player1_y")!=NULL)
                    preview_player1_y=atoi(e->Attribute("preview_player1_y"));

                int preview_player2_x=0;
                if(e->Attribute("preview_player2_x")!=NULL)
                    preview_player2_x=atoi(e->Attribute("preview_player2_x"));

                int preview_player2_y=0;
                if(e->Attribute("preview_player2_y")!=NULL)
                    preview_player2_y=atoi(e->Attribute("preview_player2_y"));

                int player1_cursor_x=0;
                if(e->Attribute("player1_cursor_x")!=NULL)
                    player1_cursor_x=atoi(e->Attribute("player1_cursor_x"));

                int player1_cursor_y=0;
                if(e->Attribute("player1_cursor_y")!=NULL)
                    player1_cursor_y=atoi(e->Attribute("player1_cursor_y"));

                int player2_cursor_x=0;
                if(e->Attribute("player2_cursor_x")!=NULL)
                    player2_cursor_x=atoi(e->Attribute("player2_cursor_x"));

                int player2_cursor_y=0;
                if(e->Attribute("player2_cursor_y")!=NULL)
                    player2_cursor_y=atoi(e->Attribute("player2_cursor_y"));

                char_select=new MenuCharSelect(painter,x,y,
                                               size_x,size_y,
                                               box_size_x,box_size_y,
                                               box_separation_x,box_separation_y,
                                               chars_player1,chars_player2,
                                               preview_player1_x,preview_player1_y,
                                               preview_player2_x,preview_player2_y,
                                               chars,
                                               player1_cursor_x,player1_cursor_y,
                                               player2_cursor_x,player2_cursor_y
                                               );
                elementos.push_back((Elemento*)char_select);

            }else if(strcmp(e->Attribute("type"),"stage_select")==0)
            {
                pos_stage=elementos_contenedor.size();
                std::vector<Elemento*>elem_lista;
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


                    elem_lista.push_back((Elemento*)new MenuImagen(painter,
                                                                   atoi(e->Attribute("x")),atoi(e->Attribute("y")),
                                                                   displacement_x,displacement_y,stop_displacement_x_at,stop_displacement_y_at,fade_in_initial,fade_in_speed,
                                                                   atoi(e->Attribute("width")),atoi(e->Attribute("height")),
                                                                   image,stages[i]
                                                                   ));
                }

                int x=atoi(e->Attribute("x"));
                int y=atoi(e->Attribute("y"));

                int arrow_left_x=x;
                if(e->Attribute("arrow_left_x"))
                    atoi(e->Attribute("arrow_left_x"));

                int arrow_left_y=y;
                if(e->Attribute("arrow_left_y"))
                    atoi(e->Attribute("arrow_left_y"));

                Image*path_left=NULL;
                if(e->Attribute("path_left")!=NULL)
                    path_left=painter->getTexture(std::string("menu/")+std::string(e->Attribute("path_left")));

                int arrow_right_x=x;
                if(e->Attribute("arrow_right_x"))
                    atoi(e->Attribute("arrow_right_x"));

                int arrow_right_y=y;
                if(e->Attribute("arrow_right_y"))
                    atoi(e->Attribute("arrow_right_y"));

                Image*path_right=NULL;
                if(e->Attribute("path_right")!=NULL)
                    path_right=painter->getTexture(std::string("menu/")+std::string(e->Attribute("path_right")));

                int arrow_left_x_selected=x;
                if(e->Attribute("arrow_left_x_selected"))
                    atoi(e->Attribute("arrow_left_x_selected"));

                int arrow_left_y_selected=y;
                if(e->Attribute("arrow_left_y_selected"))
                    atoi(e->Attribute("arrow_left_y_selected"));

                Image*path_left_selected=path_left;
                if(e->Attribute("path_left_selected")!=NULL)
                    path_left_selected=painter->getTexture(std::string("menu/")+std::string(e->Attribute("path_left_selected")));

                int arrow_right_x_selected=x;
                if(e->Attribute("arrow_right_x_selected"))
                    atoi(e->Attribute("arrow_right_x_selected"));

                int arrow_right_y_selected=y;
                if(e->Attribute("arrow_right_y_selected"))
                    atoi(e->Attribute("arrow_right_y_selected"));

                Image*path_right_selected=path_right;
                if(e->Attribute("path_right_selected")!=NULL)
                    path_right_selected=painter->getTexture(std::string("menu/")+std::string(e->Attribute("path_right_selected")));

                elementos_contenedor.push_back((Elemento*)new MenuLista(painter,x,y,
                                                                        arrow_left_x,arrow_left_y,
                                                                        path_left,
                                                                        arrow_right_x,arrow_right_y,
                                                                        path_right,
                                                                        arrow_left_x_selected,arrow_left_y_selected,
                                                                        path_left_selected,
                                                                        arrow_right_x_selected,arrow_right_y_selected,
                                                                        path_right_selected,
                                                                        elem_lista,
                                                                        "1v1"
                                                                        )
                                               );

            }
        }
    }


    for(TiXmlNode* text_node=g_node->FirstChild("text");
            text_node!=NULL;
            text_node=text_node->NextSibling("text"))
    {
        TiXmlElement* e=text_node->ToElement();

        TiXmlElement* text_span_elem=text_node->FirstChild("tspan")->ToElement();

        elementos.push_back((Elemento*)new MenuTexto(painter,atoi(e->Attribute("x")),atoi(e->Attribute("y")),
                                                     text_span_elem->GetText()
                                                     ));
    }

    selectables_container=new MenuContenedor(painter,elementos_contenedor);
    elementos.push_back((Elemento*)selectables_container);
}

Personaje* Menu::getPersonajeA(int num,bool ia)
{
    writeLogLine("Initializing player's 1 character #"+toString(num)+".");
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
    writeLogLine("Initializing player's 1 character #"+toString(num)+".");
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
    MenuContenedor *mc=((MenuContenedor*)selectables_container);
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
        if(receiver->IsKeyDownn(SDLK_q))
            return "Q";
        if(receiver->IsKeyDownn(SDLK_w))
            return "W";
        if(receiver->IsKeyDownn(SDLK_e))
            return "E";
        if(receiver->IsKeyDownn(SDLK_r))
            return "R";
        if(receiver->IsKeyDownn(SDLK_t))
            return "T";
        if(receiver->IsKeyDownn(SDLK_y))
            return "Y";
        if(receiver->IsKeyDownn(SDLK_u))
            return "U";
        if(receiver->IsKeyDownn(SDLK_i))
            return "I";
        if(receiver->IsKeyDownn(SDLK_o))
            return "O";
        if(receiver->IsKeyDownn(SDLK_p))
            return "P";
        if(receiver->IsKeyDownn(SDLK_a))
            return "A";
        if(receiver->IsKeyDownn(SDLK_s))
            return "S";
        if(receiver->IsKeyDownn(SDLK_d))
            return "D";
        if(receiver->IsKeyDownn(SDLK_f))
            return "F";
        if(receiver->IsKeyDownn(SDLK_g))
            return "G";
        if(receiver->IsKeyDownn(SDLK_h))
            return "H";
        if(receiver->IsKeyDownn(SDLK_j))
            return "J";
        if(receiver->IsKeyDownn(SDLK_k))
            return "K";
        if(receiver->IsKeyDownn(SDLK_l))
            return "L";
        if(receiver->IsKeyDownn(SDLK_z))
            return "Z";
        if(receiver->IsKeyDownn(SDLK_x))
            return "X";
        if(receiver->IsKeyDownn(SDLK_c))
            return "C";
        if(receiver->IsKeyDownn(SDLK_v))
            return "V";
        if(receiver->IsKeyDownn(SDLK_b))
            return "B";
        if(receiver->IsKeyDownn(SDLK_n))
            return "N";
        if(receiver->IsKeyDownn(SDLK_m))
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
        return SDLK_q;
    if(str==std::string("W"))
        return SDLK_w;
    if(str==std::string("E"))
        return SDLK_e;
    if(str==std::string("R"))
        return SDLK_r;
    if(str==std::string("T"))
        return SDLK_t;
    if(str==std::string("Y"))
        return SDLK_y;
    if(str==std::string("U"))
        return SDLK_u;
    if(str==std::string("I"))
        return SDLK_i;
    if(str==std::string("O"))
        return SDLK_o;
    if(str==std::string("P"))
        return SDLK_p;
    if(str==std::string("A"))
        return SDLK_a;
    if(str==std::string("S"))
        return SDLK_s;
    if(str==std::string("D"))
        return SDLK_d;
    if(str==std::string("F"))
        return SDLK_f;
    if(str==std::string("G"))
        return SDLK_g;
    if(str==std::string("H"))
        return SDLK_h;
    if(str==std::string("J"))
        return SDLK_j;
    if(str==std::string("K"))
        return SDLK_k;
    if(str==std::string("L"))
        return SDLK_l;
    if(str==std::string("Z"))
        return SDLK_z;
    if(str==std::string("X"))
        return SDLK_x;
    if(str==std::string("C"))
        return SDLK_c;
    if(str==std::string("V"))
        return SDLK_v;
    if(str==std::string("B"))
        return SDLK_b;
    if(str==std::string("N"))
        return SDLK_n;
    if(str==std::string("M"))
        return SDLK_m;
    return SDLK_ESCAPE;
}


void Menu::llenarInputsBotones()
{
    for(int i=0;i<(int)selectables_container->elementos.size();i++)
    {
        if(((MenuContenedor*)selectables_container)->elementos[i]->getTipo()=="Boton")
        {
            MenuBoton*mb=(MenuBoton*)selectables_container->elementos[i];
//            if(mb->getAccion()>=10 && mb->getAccion()<=29)
//            {
//                int player;
//                std::string mapeo="";
//                int accion=mb->getAccion();
//                if(accion>=10 && accion<=19)
//                    player=1;
//                else
//                    player=2;
//                Input* temp=new Input();
//                Input* temp2=new Input();
//                if(player==1)
//                {
//                    temp->cargarDesdeXML(1,receiver);
//                    temp2->cargarDesdeXML(2,receiver);
//                }else
//                {
//                    temp->cargarDesdeXML(2,receiver);
//                    temp2->cargarDesdeXML(1,receiver);
//                }
//                if(accion==10||accion==20)mapeo="8";
//                if(accion==11||accion==21)mapeo="2";
//                if(accion==12||accion==22)mapeo="4";
//                if(accion==13||accion==23)mapeo="6";
//                if(accion==14||accion==24)mapeo="a";
//                if(accion==15||accion==25)mapeo="b";
//                if(accion==16||accion==26)mapeo="c";
//                if(accion==17||accion==27)mapeo="d";
//                if(accion==18||accion==28)mapeo="e";
//                if(accion==19||accion==29)mapeo="f";
//
//                //key
//                mb->input_config="";
//                int pos=-1,posc=-1;
//                for(int j=0;j<(int)temp->botones.size();j++)
//                    if(temp->botones[j].getMapeo()==mapeo && !temp->botones[j].usaJoystick())
//                        pos=j;
//
//                for(int j=0;j<(int)temp->cruz.size();j++)
//                    if(temp->cruz[j].getMapeo()==mapeo && !temp->cruz[j].usaJoystick())
//                        posc=j;
//
//                if(pos!=-1)
//                    mb->input_config=temp->botones[pos].keyToString();
//
//                if(posc!=-1)
//                    mb->input_config=temp->cruz[posc].keyToString();
//
//                //joy
//                pos=-1;
//                for(int j=0;j<(int)temp->botones.size();j++)
//                    if(temp->botones[j].getMapeo()==mapeo && temp->botones[j].usaJoystick())
//                        pos=j;
//                posc=-1;
//                for(int j=0;j<(int)temp->cruz.size();j++)
//                    if(temp->cruz[j].getMapeo()==mapeo && temp->cruz[j].usaJoystick())
//                        posc=j;
//
//                if(pos!=-1)
//                {
//                    mb->input_config+=" j";
//                    mb->input_config+=toString((int)temp->botones[pos].getNumJoystick());
//                    mb->input_config+=toString((int)temp->botones[pos].joystick);
//                }
//
//                if(posc!=-1)
//                {
//                    mb->input_config+=" j";
//                    mb->input_config+=toString((int)temp->cruz[posc].getNumJoystick());
//                    mb->input_config+="-";
//                    if(temp->cruz[posc].joystick==-8)
//                        mb->input_config+=std::string("up");
//                    else if(temp->cruz[posc].joystick==-2)
//                        mb->input_config+=std::string("down");
//                    else if(temp->cruz[posc].joystick==-4)
//                        mb->input_config+=std::string("left");
//                    else if(temp->cruz[posc].joystick==-6)
//                        mb->input_config+=std::string("right");
//                    else
//                        mb->input_config+=toString((int)temp->cruz[posc].joystick);
//                }
//            }
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
        0.0,
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
            0.0,
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
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            false);
    }
    painter->updateScreen();
}
