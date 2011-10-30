#include "../include/Menu.h"
Menu::Menu(Stage* stage,Personaje *pa,Personaje *pb,Grafico* grafico,Receiver* receiver)
{
    this->stage=stage;
    this->pa=pa;
    this->pb=pb;
    this->grafico=grafico;
    this->receiver=receiver;
    cargarDesdeXml((char*)"menu/menu.xml");

//    elementos.push_back((Elemento*)new MenuImagen(0,0,1024,600,true,grafico->getTexture("menu/fondo.png")));
//    elementos.push_back((Elemento*)new MenuTexto(0,0,100,100,true,"L. GPL",video::SColor(255,255,255,255)));
//    elementos.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"V. 1.0",video::SColor(255,255,255,255)));
//    elementos.push_back((Elemento*)new MenuImagen(300,0,400,283,true,grafico->getTexture("menu/logo.png")));
//
//
//    vector<Elemento*>elementos_contenedor;
//    elementos_contenedor.push_back((Elemento*)new MenuBoton(0,0,150,50,true,
//                                                            grafico->getTexture("menu/fondo_boton.png"),5,5,"Iniciar",video::SColor(255,255,255,255),
//                                                            grafico->getTexture("menu/fondo_boton2.png"),5,5,"Iniciar",video::SColor(255,0,0,0),
//                                                            0
//                                                            ));
//    vector<Elemento*>elem_lista;
//    elem_lista.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"Ryu",video::SColor(255,255,255,255)));
//    elem_lista.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"Ken",video::SColor(255,255,255,255)));
//    elem_lista.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"Sakura",video::SColor(255,255,255,255)));
//    elementos_contenedor.push_back((Elemento*)new MenuLista(0,30,50,50,true,
//                                                            -50,0,grafico->getTexture("menu/flecha_izq.png"),150,0,grafico->getTexture("menu/flecha_der.png"),
//                                                            -50,0,grafico->getTexture("menu/flecha_izq2.png"),150,0,grafico->getTexture("menu/flecha_der2.png"),
//                                                            elem_lista
//                                                            ));
//    vector<Elemento*>elem_lista2;
//    elem_lista2.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"Stage1",video::SColor(255,255,255,255)));
//    elem_lista2.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"Stage2",video::SColor(255,255,255,255)));
//    elem_lista2.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"Stage3",video::SColor(255,255,255,255)));
//    elementos_contenedor.push_back((Elemento*)new MenuLista(0,60,50,50,true,
//                                    -50,0,grafico->getTexture("menu/flecha_izq.png"),150,0,grafico->getTexture("menu/flecha_der.png"),
//                                    -50,0,grafico->getTexture("menu/flecha_izq2.png"),150,0,grafico->getTexture("menu/flecha_der2.png"),
//                                    elem_lista2));
//    elementos_contenedor.push_back((Elemento*)new MenuBarra(0,120,200,50,true,
//                                                            grafico->getTexture("menu/fondo_boton.png"),0,0,grafico->getTexture("menu/barra.png"),
//                                                            grafico->getTexture("menu/fondo_boton2.png"),0,0,grafico->getTexture("menu/barra.png"),
//                                                            5,3));
//    elementos_contenedor.push_back((Elemento*)new MenuBoton(0,180,150,50,true,
//                                                            grafico->getTexture("menu/fondo_boton.png"),5,5,"Salir",video::SColor(255,255,255,255),
//                                                            grafico->getTexture("menu/fondo_boton2.png"),5,5,"Salir",video::SColor(255,0,0,0),
//                                                            1
//                                                            ));
//
//    elementos.push_back((Elemento*)new MenuContenedor(400,270,500,500,true,elementos_contenedor));
//
//    contenedor_actual=(MenuContenedor*)elementos[4];
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
        if(!pa->input->receiver->IsKeyDown(irr::KEY_LEFT)
           && !pa->input->receiver->IsKeyDown(irr::KEY_RIGHT)
           && !pa->input->receiver->IsKeyDown(irr::KEY_UP)
           && !pa->input->receiver->IsKeyDown(irr::KEY_DOWN)
           && !pa->input->receiver->IsKeyDown(irr::KEY_RETURN)
           )
            tecla_arriba=true;
        if(tecla_arriba)
        {
            tecla_arriba=false;
            if(pa->input->receiver->IsKeyDown(irr::KEY_DOWN))
            {
                ((MenuContenedor*)contenedor_actual)->avanzar();
            }
            else if(pa->input->receiver->IsKeyDown(irr::KEY_UP))
            {
                ((MenuContenedor*)contenedor_actual)->retroceder();
            }
            else if(pa->input->receiver->IsKeyDown(irr::KEY_RIGHT))
            {
                if(((MenuContenedor*)contenedor_actual)->getSeleccionado()->getTipo()==5)
                {
                    ((MenuLista*)((MenuContenedor*)contenedor_actual)->getSeleccionado())->avanzar();
                }
                if(((MenuContenedor*)contenedor_actual)->getSeleccionado()->getTipo()==6)
                {
                    ((MenuBarra*)((MenuContenedor*)contenedor_actual)->getSeleccionado())->avanzar();
                }
            }
            else if(pa->input->receiver->IsKeyDown(irr::KEY_LEFT))
            {
                if(((MenuContenedor*)contenedor_actual)->getSeleccionado()->getTipo()==5)
                {
                    ((MenuLista*)((MenuContenedor*)contenedor_actual)->getSeleccionado())->retroceder();
                }
                if(((MenuContenedor*)contenedor_actual)->getSeleccionado()->getTipo()==6)
                {
                    ((MenuBarra*)((MenuContenedor*)contenedor_actual)->getSeleccionado())->retroceder();
                }
            }else if(pa->input->receiver->IsKeyDown(irr::KEY_RETURN))
            {
                if(((MenuContenedor*)contenedor_actual)->getSeleccionado()->getTipo()==4)
                {
                    MenuBoton*mb=((MenuBoton*)((MenuContenedor*)contenedor_actual)->getSeleccionado());
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
            elementos[i]->dibujar(grafico);
        grafico->endScene();
    }
    grafico->run();
}

    TiXmlDocument abrirXml(char* archivo)
    {
        TiXmlDocument doc( archivo );
        doc.LoadFile();
        return doc;
    }

void Menu::cargarDesdeXml(char* archivo)
{
    TiXmlDocument doc_t=abrirXml((char*)archivo);
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
            elementos.push_back((Elemento*)new MenuImagen(atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("height")),atoi(e->Attribute("width")),strcmp(e->Attribute("visible"),"true")==0,
                                                          grafico->getTexture(irr::io::path(path))));
        }else if(strcmp(e->Value(),"Text")==0)
        {
                elementos.push_back((Elemento*)new MenuTexto(atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("height")),atoi(e->Attribute("width")),strcmp(e->Attribute("visible"),"true")==0,
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
                    elementos_contenedor.push_back((Elemento*)new MenuBoton(atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("height")),atoi(ec->Attribute("width")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path"))),atoi(ec->Attribute("text_x")),atoi(ec->Attribute("text_y")),ec->Attribute("text"),video::SColor(atoi(ec->Attribute("alpha")),atoi(ec->Attribute("red")),atoi(ec->Attribute("green")),atoi(ec->Attribute("blue"))),
                                                                            grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_selected"))),atoi(ec->Attribute("text_x_selected")),atoi(ec->Attribute("text_y_selected")),ec->Attribute("text_selected"),video::SColor(atoi(ec->Attribute("alpha_selected")),atoi(ec->Attribute("red_selected")),atoi(ec->Attribute("green_selected")),atoi(ec->Attribute("blue_selected"))),
                                                                            atoi(ec->Attribute("action_id"))
                                                                            ));
                }
                if(strcmp(ec->Value(),"Bar")==0)
                {
                    elementos_contenedor.push_back((Elemento*)new MenuBarra(atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("height")),atoi(ec->Attribute("width")),strcmp(ec->Attribute("visible"),"true")==0,
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
                            elem_lista.push_back((Elemento*)new MenuTexto(atoi(ec->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
                                                             el->Attribute("text"),video::SColor(atoi(el->Attribute("alpha")),atoi(el->Attribute("red")),atoi(el->Attribute("green")),atoi(el->Attribute("blue")))
                                                             ));
                        if(strcmp(el->Value(),"Image")==0)
                        {
                            stringw path(el->Attribute("path"));
                            stringw dir("menu/");
                            path=dir+path;
                            elem_lista.push_back((Elemento*)new MenuImagen(atoi(el->Attribute("x")),atoi(el->Attribute("y")),atoi(el->Attribute("height")),atoi(el->Attribute("width")),strcmp(el->Attribute("visible"),"true")==0,
                                                                          grafico->getTexture(irr::io::path(path))));
                        }
                    }
                    elementos_contenedor.push_back((Elemento*)new MenuLista(atoi(ec->Attribute("x")),atoi(ec->Attribute("y")),atoi(ec->Attribute("height")),atoi(ec->Attribute("width")),strcmp(ec->Attribute("visible"),"true")==0,
                                                                            atoi(ec->Attribute("arrow_left_x")),atoi(ec->Attribute("arrow_left_y")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_left"))),
                                                                            atoi(ec->Attribute("arrow_right_x")),atoi(ec->Attribute("arrow_right_y")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_right"))),
                                                                            //atoi(ec->Attribute("arrow_right_x")),0,grafico->getTexture("menu/flecha_izq2.png"),150,0,grafico->getTexture("menu/flecha_der2.png"),
                                                                            atoi(ec->Attribute("arrow_left_x_selected")),atoi(ec->Attribute("arrow_left_y_selected")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_left_selected"))),
                                                                            atoi(ec->Attribute("arrow_right_x_selected")),atoi(ec->Attribute("arrow_right_y_selected")),grafico->getTexture(stringw("menu/")+stringw(ec->Attribute("path_right_selected"))),
                                                                            elem_lista
                                                                            ));
                }
            }
            elementos.push_back((Elemento*)new MenuContenedor(atoi(e->Attribute("x")),atoi(e->Attribute("y")),atoi(e->Attribute("height")),atoi(e->Attribute("width")),strcmp(e->Attribute("visible"),"true")
                                                              ,elementos_contenedor));
        }
    }
    contenedor_actual=(MenuContenedor*)elementos[4];
}
