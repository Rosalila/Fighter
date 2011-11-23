#include "Menu/Menu.h"
Menu::Menu(Grafico* grafico,Receiver* receiver)
{
    this->grafico=grafico;
    this->receiver=receiver;

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

    cargarDesdeXml((char*)"menu/menu.xml",chars,stages);
}

void Menu::loopMenu()
{
    bool tecla_arriba=true;
	for (;;)
	{
	    //setear frames a "60"
	    grafico->device->getTimer()->start();
	    for(u32 t=grafico->device->getTimer()->getTime();
            t+16>grafico->device->getTimer()->getTime();
            grafico->device->getTimer()->tick()
         );
        dibujarMenu();
        if(!receiver->IsKeyDown(irr::KEY_LEFT)
           && !receiver->IsKeyDown(irr::KEY_RIGHT)
           && !receiver->IsKeyDown(irr::KEY_UP)
           && !receiver->IsKeyDown(irr::KEY_DOWN)
           && !receiver->IsKeyDown(irr::KEY_RETURN)
           )
            tecla_arriba=true;
        if(tecla_arriba)
        {
            tecla_arriba=false;
            if(receiver->IsKeyDown(irr::KEY_DOWN))
            {
                ((MenuContenedor*)contenedor_actual)->avanzar();
            }
            else if(receiver->IsKeyDown(irr::KEY_UP))
            {
                ((MenuContenedor*)contenedor_actual)->retroceder();
            }
            else if(receiver->IsKeyDown(irr::KEY_RIGHT))
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
            else if(receiver->IsKeyDown(irr::KEY_LEFT))
            {
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==5)
                {
                    ((MenuLista*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado())->retroceder();
                }
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==6)
                {
                    ((MenuBarra*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado())->retroceder();
                }
            }else if(receiver->IsKeyDown(irr::KEY_RETURN))
            {
                if(((MenuContenedor*)contenedor_actual)->getElementoSeleccionado()->getTipo()==4)
                {
                    MenuBoton*mb=((MenuBoton*)((MenuContenedor*)contenedor_actual)->getElementoSeleccionado());
                    if(mb->getAccion()==0)
                        break;
                    if(mb->getAccion()==1)
                        exit(0);
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
    for(TiXmlNode* elemento=doc->FirstChild();
            elemento!=NULL;
            elemento=elemento->NextSibling())
    {
        TiXmlElement* e=elemento->ToElement();
        cout<<e->Value()<<endl;
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
                    elementos_contenedor.push_back((Elemento*)new MenuBoton(grafico,atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("height")),atoi(ec->Attribute("width")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path"))),atoi(ec->Attribute("text_x")),atoi(ec->Attribute("text_y")),ec->Attribute("text"),video::SColor(atoi(ec->Attribute("alpha")),atoi(ec->Attribute("red")),atoi(ec->Attribute("green")),atoi(ec->Attribute("blue"))),
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_selected"))),atoi(ec->Attribute("text_x_selected")),atoi(ec->Attribute("text_y_selected")),ec->Attribute("text_selected"),video::SColor(atoi(ec->Attribute("alpha_selected")),atoi(ec->Attribute("red_selected")),atoi(ec->Attribute("green_selected")),atoi(ec->Attribute("blue_selected"))),
                                                                            atoi(ec->Attribute("action_id"))
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
                            for(int i=0;i<(int)chars.size();i++)
                            elem_lista.push_back((Elemento*)new MenuTexto(grafico,atoi(ec->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
                                                             chars[i],video::SColor(atoi(el->Attribute("alpha")),atoi(el->Attribute("red")),atoi(el->Attribute("green")),atoi(el->Attribute("blue")))
                                                             ));
                        }
                        if(strcmp(el->Value(),"stage")==0)
                        {
                            for(int i=0;i<(int)stages.size();i++)
                            elem_lista.push_back((Elemento*)new MenuTexto(grafico,atoi(ec->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
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
            elementos.push_back((Elemento*)new MenuContenedor(grafico,atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("height")),atoi(e->Attribute("width")),strcmp(e->Attribute("visible"),"true")
                                                              ,elementos_contenedor));
        }
    }
    contenedor_actual=(MenuContenedor*)elementos[4];
}

char* Menu::getPersonajeA()
{
    MenuContenedor *mc=(MenuContenedor*)elementos[4];
    MenuLista *ml=(MenuLista*)mc->elementos[1];
    MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
    stringw s2=mt->texto;
    char *str = new char[255];
    sprintf(str,"%ls",s2.c_str());
    return str;
}

char* Menu::getPersonajeB()
{
    MenuContenedor *mc=(MenuContenedor*)elementos[4];
    MenuLista *ml=(MenuLista*)mc->elementos[2];
    MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
    stringw s2=mt->texto;
    char *str = new char[255];
    sprintf(str,"%ls",s2.c_str());
    return str;
}

char* Menu::getStage()
{
    MenuContenedor *mc=(MenuContenedor*)elementos[4];
    MenuLista *ml=(MenuLista*)mc->elementos[3];
    MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
    stringw s2=mt->texto;
    char *str = new char[255];
    sprintf(str,"%ls",s2.c_str());
    return str;
}
