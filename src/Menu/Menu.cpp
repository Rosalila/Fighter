#include "Menu/Menu.h"
Menu::Menu(Grafico* grafico,Receiver* receiver,Sonido* sonido,char* archivo)
{
    for(int i=0;i<3;i++)
        pos_pa.push_back(0);
    for(int i=0;i<3;i++)
        pos_pb.push_back(0);
    this->grafico=grafico;
    this->receiver=receiver;
    this->sonido=sonido;
    this->exit_signal=false;
    this->save_inputs_signal=false;

        TiXmlDocument doc_t((char*)"config.xml");
        doc_t.LoadFile();
        TiXmlDocument *doc;
        doc=&doc_t;

        vector<stringw> chars,stages;
		for(TiXmlNode* node_chars=doc->FirstChild("Chars");
                node_chars!=NULL;
                node_chars=node_chars->NextSibling("Chars"))
        {
            for(TiXmlNode* node_chars2=node_chars->FirstChild("char");
                    node_chars2!=NULL;
                    node_chars2=node_chars2->NextSibling("char"))
            {
                chars.push_back(stringw(node_chars2->ToElement()->Attribute("nombre")));
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
                stages.push_back(stringw(node_chars2->ToElement()->Attribute("nombre")));
            }
        }

    cargarDesdeXml(archivo,chars,stages);
}

void Menu::loopMenu()
{
    bool tecla_arriba=true;
    sonido->reproducirSonido(stringw("Menu.music"));

    llenarInputsBotones();
    //inicio
	for (;;)
	{
	    receiver->endEventProcess();
	    receiver->startEventProcess();
	    //setear frames a "60"
	    grafico->device->getTimer()->start();
	    for(u32 t=grafico->device->getTimer()->getTime();
            t+16>grafico->device->getTimer()->getTime();
            grafico->device->getTimer()->tick()
         );
        dibujarMenu();
        if(!receiver->IsKeyDownn(irr::KEY_LEFT)
           && !receiver->IsKeyDownn(irr::KEY_RIGHT)
           && !receiver->IsKeyDownn(irr::KEY_UP)
           && !receiver->IsKeyDownn(irr::KEY_DOWN)
           && !receiver->IsKeyDownn(irr::KEY_RETURN)
           )
            tecla_arriba=true;
        if(tecla_arriba)
        {
            tecla_arriba=false;
            if(receiver->IsKeyDownn(irr::KEY_DOWN))
            {
                ((MenuContenedor*)contenedor_actual)->avanzar();
            }
            else if(receiver->IsKeyDownn(irr::KEY_UP))
            {
                ((MenuContenedor*)contenedor_actual)->retroceder();
            }
            else if(receiver->IsKeyDownn(irr::KEY_RIGHT))
            {
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==5)
                {
                    ((MenuLista*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado())->avanzar();
                }
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==6)
                {
                    ((MenuBarra*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado())->avanzar();
                }
            }
            else if(receiver->IsKeyDownn(irr::KEY_LEFT))
            {
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==5)
                {
                    ((MenuLista*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado())->retroceder();
                }
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==6)
                {
                    ((MenuBarra*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado())->retroceder();
                }
            }else if(receiver->IsKeyPressed(irr::KEY_RETURN))
            {
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==4)
                {
                    MenuBoton*mb=((MenuBoton*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    if(mb->getAccion()==0)
                    {
                        inputa=new Input();
                        inputb=new Input();
                        //this->inputa->cargarIAXML(1);
                        inputa->cargarDesdeXML(1,receiver);
                        inputb->cargarDesdeXML(2,receiver);

                        char *path_s=new char[255];
                        strcpy(path_s,"stages/");
                        strcat(path_s,(char*)getStage());
                        strcat(path_s,"/");

                        Personaje* p1a=getPersonajeA(0,false);
                        Personaje* p1b=getPersonajeB(0,false);
                        p1a->personaje_contrario=p1b;
                        p1b->personaje_contrario=p1a;

                        Personaje* p2a=getPersonajeA(1,false);
                        Personaje* p2b=getPersonajeB(1,false);
                        p2a->personaje_contrario=p1b;
                        p2b->personaje_contrario=p1a;

                        Personaje* p3a=getPersonajeA(2,false);
                        Personaje* p3b=getPersonajeB(2,false);
                        p3a->personaje_contrario=p1b;
                        p3b->personaje_contrario=p1a;

                        pa.push_back(p1a);
                        pa.push_back(p2a);
                        pa.push_back(p3a);

                        pb.push_back(p1b);
                        pb.push_back(p2b);
                        pb.push_back(p3b);

                        stage=new Stage(grafico,sonido);
                        stage->cargarDesdeXML((char*)path_s);

                        break;
                    }

                    if(mb->getAccion()==1)
                    {
                        char *path_s=new char[255];
                        strcpy(path_s,"stages/");
                        strcat(path_s,(char*)getStage());
                        strcat(path_s,"/");

                        Personaje* p1a=getPersonajeA(0,false);
                        Personaje* p1b=getPersonajeB(0,true);
                        p1a->personaje_contrario=p1b;
                        p1b->personaje_contrario=p1a;

                        Personaje* p2a=getPersonajeA(1,false);
                        Personaje* p2b=getPersonajeB(1,true);
                        p2a->personaje_contrario=p1b;
                        p2b->personaje_contrario=p1a;

                        Personaje* p3a=getPersonajeA(2,false);
                        Personaje* p3b=getPersonajeB(2,true);
                        p3a->personaje_contrario=p1b;
                        p3b->personaje_contrario=p1a;

                        pa.push_back(p1a);
                        pa.push_back(p2a);
                        pa.push_back(p3a);

                        pb.push_back(p1b);
                        pb.push_back(p2b);
                        pb.push_back(p3b);

                        stage=new Stage(grafico,sonido);
                        stage->cargarDesdeXML((char*)path_s);

                        break;
                    }
                    if(mb->getAccion()==2)
                        break;
                    if(mb->getAccion()==3)
                    {
                        exit_signal=true;
                        break;
                    }
                    if(mb->getAccion()==4)
                    {
                        Menu *temp=new Menu(grafico,receiver,sonido,(char*)"menu/input_menu.xml");
                        temp->loopMenu();
                    }
                    if(mb->getAccion()>=10 && mb->getAccion()<=29)
                    {
                        int player;
                        stringw mapeo="";
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
                        stringw str_input=getInputPressed();
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
	sonido->pararSonido("Menu.music");
}

void Menu::dibujarMenu()
{
    if (grafico->isWindowActive())
    {
        grafico->beginScene();

        for(int i=0;i<(int)elementos.size();i++)
            elementos[i]->dibujar();
        grafico->endScene();
    }
    grafico->run();
}

void Menu::cargarDesdeXml(char* archivo,vector<stringw> chars,vector<stringw> stages)
{
    TiXmlDocument doc_t( archivo );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    sonido->agregarSonido("Menu.music","menu/music.ogg");

    for(TiXmlNode* elemento=doc->FirstChild();
            elemento!=NULL;
            elemento=elemento->NextSibling())
    {
        TiXmlElement* e=elemento->ToElement();
        if(strcmp(e->Value(),"Image")==0)
        {
            stringw path(e->Attribute("path"));
            stringw dir("menu/");
            path=dir+path;
            elementos.push_back((Elemento*)new MenuImagen(grafico,atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("height")),atoi(e->Attribute("width")),strcmp(e->Attribute("visible"),"true")==0,
                                                          grafico->getTexture(irr::io::path(path))));
        }else if(strcmp(e->Value(),"Text")==0)
        {
                elementos.push_back((Elemento*)new MenuTexto(grafico,atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("height")),atoi(e->Attribute("width")),strcmp(e->Attribute("visible"),"true")==0,
                                                             e->Attribute("text"),video::SColor(atoi(e->Attribute("alpha")),atoi(e->Attribute("red")),atoi(e->Attribute("green")),atoi(e->Attribute("blue")))
                                                             ));
        }else if(strcmp(e->Value(),"Container")==0)
        {
            vector<Elemento*>elementos_contenedor;
            for(TiXmlNode* elem_container=elemento->FirstChild();
                    elem_container!=NULL;
                    elem_container=elem_container->NextSibling())
            {
                TiXmlElement* ec=elem_container->ToElement();
                if(strcmp(ec->Value(),"Button")==0)
                {
                    int action=-1;
                    if(strcmp(ec->Attribute("action"),"PvP")==0)
                        action=0;
                    if(strcmp(ec->Attribute("action"),"PvCPU")==0)
                        action=1;
                    if(strcmp(ec->Attribute("action"),"Continue")==0)
                        action=2;
                    if(strcmp(ec->Attribute("action"),"Exit")==0)
                        action=3;
                    if(strcmp(ec->Attribute("action"),"InputConfig")==0)
                        action=4;

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

                    elementos_contenedor.push_back((Elemento*)new MenuBoton(grafico,atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("height")),atoi(ec->Attribute("width")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path"))),atoi(ec->Attribute("text_x")),atoi(ec->Attribute("text_y")),ec->Attribute("text"),video::SColor(atoi(ec->Attribute("alpha")),atoi(ec->Attribute("red")),atoi(ec->Attribute("green")),atoi(ec->Attribute("blue"))),
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_selected"))),atoi(ec->Attribute("text_x_selected")),atoi(ec->Attribute("text_y_selected")),ec->Attribute("text_selected"),video::SColor(atoi(ec->Attribute("alpha_selected")),atoi(ec->Attribute("red_selected")),atoi(ec->Attribute("green_selected")),atoi(ec->Attribute("blue_selected"))),
                                                                            action
                                                                            ));
                }
                if(strcmp(ec->Value(),"Bar")==0)
                {
                    elementos_contenedor.push_back((Elemento*)new MenuBarra(grafico,atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("height")),atoi(ec->Attribute("width")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_bg"))),atoi(ec->Attribute("bar_x")),atoi(ec->Attribute("bar_y")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path"))),
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_bg_selected"))),atoi(ec->Attribute("bar_x_selected")),atoi(ec->Attribute("bar_y_selected")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_selected"))),
                                                                            atoi(ec->Attribute("max")),atoi(ec->Attribute("default_value"))));
                }
                if(strcmp(ec->Value(),"List")==0)
                {
                    vector<Elemento*>elem_lista;

                    for(TiXmlNode* elem_list=elem_container->FirstChild();
                            elem_list!=NULL;
                            elem_list=elem_list->NextSibling())
                    {
                        TiXmlElement* el=elem_list->ToElement();
                        if(strcmp(el->Value(),"Text")==0)
                            elem_lista.push_back((Elemento*)new MenuTexto(grafico,atoi(ec->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
                                                             el->Attribute("text"),video::SColor(atoi(el->Attribute("alpha")),atoi(el->Attribute("red")),atoi(el->Attribute("green")),atoi(el->Attribute("blue")))
                                                             ));
                        if(strcmp(el->Value(),"Image")==0)
                        {
                            stringw path(el->Attribute("path"));
                            stringw dir("menu/");
                            path=dir+path;
                            elem_lista.push_back((Elemento*)new MenuImagen(grafico,atoi(el->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
                                                                          grafico->getTexture(irr::io::path(path))));
                        }
                        if(strcmp(el->Value(),"chars")==0)
                        {
                            int player=atoi(el->Attribute("player"));
                            int pos=atoi(el->Attribute("number"));
                            if(player==1)
                                pos_pa[pos]=elementos_contenedor.size();
                            if(player==2)
                                pos_pb[pos]=elementos_contenedor.size();
                            for(int i=0;i<(int)chars.size();i++)
                            elem_lista.push_back((Elemento*)new MenuTexto(grafico,atoi(el->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
                                                             chars[i],video::SColor(atoi(el->Attribute("alpha")),atoi(el->Attribute("red")),atoi(el->Attribute("green")),atoi(el->Attribute("blue")))
                                                             ));
                        }
                        if(strcmp(el->Value(),"stage")==0)
                        {
                            pos_stage=elementos_contenedor.size();
                            for(int i=0;i<(int)stages.size();i++)
                            elem_lista.push_back((Elemento*)new MenuTexto(grafico,atoi(el->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
                                                             stages[i],video::SColor(atoi(el->Attribute("alpha")),atoi(el->Attribute("red")),atoi(el->Attribute("green")),atoi(el->Attribute("blue")))
                                                             ));
                        }
                    }
                    elementos_contenedor.push_back((Elemento*)new MenuLista(grafico,atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("height")),atoi(ec->Attribute("width")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            atoi(ec->Attribute("arrow_left_x")),atoi(ec->Attribute("arrow_left_y")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_left"))),
                                                                            atoi(ec->Attribute("arrow_right_x")),atoi(ec->Attribute("arrow_right_y")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_right"))),
                                                                            //atoi(ec->Attribute("arrow_right_x")),0,grafico->getTexture("menu/flecha_izq2.png"),150,0,grafico->getTexture("menu/flecha_der2.png"),
                                                                            atoi(ec->Attribute("arrow_left_x_selected")),atoi(ec->Attribute("arrow_left_y_selected")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_left_selected"))),
                                                                            atoi(ec->Attribute("arrow_right_x_selected")),atoi(ec->Attribute("arrow_right_y_selected")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_right_selected"))),
                                                                            elem_lista
                                                                            ));
                }
            }
            contenedor_actual=new MenuContenedor(grafico,atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("height")),atoi(e->Attribute("width")),strcmp(e->Attribute("visible"),"true")
                                                              ,elementos_contenedor);
            elementos.push_back((Elemento*)contenedor_actual);
        }
    }
}

Personaje* Menu::getPersonajeA(int num,bool ia)
{
    //get string
    MenuContenedor *mc=(MenuContenedor*)elementos[4];
    MenuLista *ml=(MenuLista*)mc->elementos[pos_pa[num]];
    MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
    stringw s2=mt->texto;
    char *str = new char[255];
    sprintf(str,"%ls",s2.c_str());

    //get cadena
    char *path_a=new char[255];
    strcpy(path_a,"");
    strcat(path_a,str);

    if(ia)
    {
        inputa=new Input();
        char*file_ia=new char[255];
        strcpy(file_ia,"chars/");
        strcat(file_ia,path_a);
        strcat(file_ia,"/ia.xml");
        inputa->cargarIAXML(2,file_ia);
    }else
    {
        inputa=new Input();
        inputa->cargarDesdeXML(1,receiver);
    }

    //get char
    Personaje* p=new Personaje(grafico,sonido,1);
    p->cargarDesdeXML(300,370,inputa,(char *)path_a);
    return p;
}

Personaje* Menu::getPersonajeB(int num,bool ia)
{
    //get string
    MenuContenedor *mc=(MenuContenedor*)elementos[4];
    MenuLista *ml=(MenuLista*)mc->elementos[pos_pb[num]];
    MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
    stringw s2=mt->texto;
    char *str = new char[255];
    sprintf(str,"%ls",s2.c_str());

    //get string
    char *path_b=new char[255];
    strcpy(path_b,"");
    strcat(path_b,str);

    if(ia)
    {
        inputb=new Input();
        char*file_ia=new char[255];
        strcpy(file_ia,"chars/");
        strcat(file_ia,path_b);
        strcat(file_ia,"/ai.xml");
        inputb->cargarIAXML(2,file_ia);
    }else
    {
        inputb=new Input();
        inputb->cargarDesdeXML(2,receiver);
    }

    //get char
    Personaje* p=new Personaje(grafico,sonido,2);
    p->cargarDesdeXML(524,370,inputb,(char *)path_b);
    return p;
}

char* Menu::getStage()
{
    MenuContenedor *mc=(MenuContenedor*)elementos[4];
    MenuLista *ml=(MenuLista*)mc->elementos[pos_stage];
    MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
    stringw s2=mt->texto;
    char *str = new char[255];
    sprintf(str,"%ls",s2.c_str());
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

stringw Menu::getInputPressed()
{
    while(true)
    {
        receiver->endEventProcess();
        receiver->startEventProcess();
        //setear frames a "60"
        grafico->device->getTimer()->start();
        for(u32 t=grafico->device->getTimer()->getTime();
            t+16>grafico->device->getTimer()->getTime();
            grafico->device->getTimer()->tick()
         );
        dibujarMenu();
        if(receiver->IsKeyDownn(irr::KEY_KEY_Q))
            return "Q";
        if(receiver->IsKeyDownn(irr::KEY_KEY_W))
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

irr::EKEY_CODE Menu::toKeyCode(stringw str)
{
    if(str==stringw("Q"))
        return irr::KEY_KEY_Q;
    if(str==stringw("W"))
        return irr::KEY_KEY_W;
    if(str==stringw("E"))
        return irr::KEY_KEY_E;
    if(str==stringw("R"))
        return irr::KEY_KEY_R;
    if(str==stringw("T"))
        return irr::KEY_KEY_T;
    if(str==stringw("Y"))
        return irr::KEY_KEY_Y;
    if(str==stringw("U"))
        return irr::KEY_KEY_U;
    if(str==stringw("I"))
        return irr::KEY_KEY_I;
    if(str==stringw("O"))
        return irr::KEY_KEY_O;
    if(str==stringw("P"))
        return irr::KEY_KEY_P;
    if(str==stringw("A"))
        return irr::KEY_KEY_A;
    if(str==stringw("S"))
        return irr::KEY_KEY_S;
    if(str==stringw("D"))
        return irr::KEY_KEY_D;
    if(str==stringw("F"))
        return irr::KEY_KEY_F;
    if(str==stringw("G"))
        return irr::KEY_KEY_G;
    if(str==stringw("H"))
        return irr::KEY_KEY_H;
    if(str==stringw("J"))
        return irr::KEY_KEY_J;
    if(str==stringw("K"))
        return irr::KEY_KEY_K;
    if(str==stringw("L"))
        return irr::KEY_KEY_L;
    if(str==stringw("Z"))
        return irr::KEY_KEY_Z;
    if(str==stringw("X"))
        return irr::KEY_KEY_X;
    if(str==stringw("C"))
        return irr::KEY_KEY_C;
    if(str==stringw("V"))
        return irr::KEY_KEY_V;
    if(str==stringw("B"))
        return irr::KEY_KEY_B;
    if(str==stringw("N"))
        return irr::KEY_KEY_N;
    if(str==stringw("M"))
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
                stringw mapeo="";
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
                    //cout<<temp->botones[pos].joystick<<endl;
                    mb->input_config+=stringw((int)temp->botones[pos].getNumJoystick());
                    mb->input_config+=stringw((int)temp->botones[pos].joystick);
                }

                if(posc!=-1)
                {
                    mb->input_config+=" j";
                    //cout<<temp->botones[pos].joystick<<endl;
                    mb->input_config+=stringw((int)temp->cruz[posc].getNumJoystick());
                    mb->input_config+="-";
                    if(temp->cruz[posc].joystick==-8)
                        mb->input_config+=stringw("up");
                    else if(temp->cruz[posc].joystick==-2)
                        mb->input_config+=stringw("down");
                    else if(temp->cruz[posc].joystick==-4)
                        mb->input_config+=stringw("left");
                    else if(temp->cruz[posc].joystick==-6)
                        mb->input_config+=stringw("right");
                    else
                        mb->input_config+=stringw((int)temp->cruz[posc].joystick);
                }
            }
        }
    }
}
