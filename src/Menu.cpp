#include "../include/Menu.h"
Menu::Menu(Stage* stage,Personaje *pa,Personaje *pb,Grafico* grafico,Receiver* receiver)
{
    this->stage=stage;
    this->pa=pa;
    this->pb=pb;
    this->grafico=grafico;
    this->receiver=receiver;

    elementos.push_back((Elemento*)new MenuImagen(0,0,1024,600,true,grafico->getTexture("menus/fondo.png")));
    elementos.push_back((Elemento*)new MenuTexto(0,0,100,100,true,"L. GPL",video::SColor(255,255,255,255)));
    elementos.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"V. 1.0",video::SColor(255,255,255,255)));
    elementos.push_back((Elemento*)new MenuImagen(300,0,400,283,true,grafico->getTexture("menus/logo.png")));


    vector<Elemento*>elementos_contenedor;
    elementos_contenedor.push_back((Elemento*)new MenuBoton(0,0,150,50,true,
                                                            grafico->getTexture("menus/fondo_boton.png"),5,5,"Iniciar",video::SColor(255,255,255,255),
                                                            grafico->getTexture("menus/fondo_boton2.png"),5,5,"Iniciarr",video::SColor(255,0,0,0)
                                                            ));
    vector<Elemento*>elem_lista;
    elem_lista.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"RyuSf2",video::SColor(255,255,255,255)));
    elementos_contenedor.push_back((Elemento*)new MenuLista(0,30,50,50,true,
                                                            -50,0,grafico->getTexture("menus/flecha_izq.png"),150,0,grafico->getTexture("menus/flecha_der.png"),
                                                            -50,0,grafico->getTexture("menus/flecha_izq2.png"),150,0,grafico->getTexture("menus/flecha_der2.png"),
                                                            elem_lista
                                                            ));
    vector<Elemento*>elem_lista2;
    elem_lista2.push_back((Elemento*)new MenuTexto(0,20,100,100,true,"Stage1",video::SColor(255,255,255,255)));
    elementos_contenedor.push_back((Elemento*)new MenuLista(0,60,50,50,true,
                                    -50,0,grafico->getTexture("menus/flecha_izq.png"),150,0,grafico->getTexture("menus/flecha_der.png"),
                                    -50,0,grafico->getTexture("menus/flecha_izq2.png"),150,0,grafico->getTexture("menus/flecha_der2.png"),
                                    elem_lista2));
    elementos_contenedor.push_back((Elemento*)new MenuBarra(0,120,200,50,true,
                                                            grafico->getTexture("menus/fondo_boton.png"),0,0,grafico->getTexture("menus/barra.png"),
                                                            grafico->getTexture("menus/fondo_boton2.png"),0,0,grafico->getTexture("menus/barra.png"),
                                                            5,3));

    elementos.push_back((Elemento*)new MenuContenedor(400,270,500,500,true,elementos_contenedor));

    //elementos[4]=(Elemento*)mc;


    //vector<Elemento*> contenedor;
    //contenedor.push_back((Elemento*)new MenuImagen(0,0,100,100,true,grafico->getTexture("menus/Rosalila01.png")));
    //elementos.push_back((Elemento*)new MenuContenedor(0,0,100,100,true,contenedor));
    //elementos.push_back(new MenuImagen(0,0,100,100,true,grafico->getTexture("menus/Rosalila01.png")));
}

void Menu::loopMenu()
{
	for (;!pa->input->receiver->IsKeyDown(irr::KEY_KEY_0);)
	{
	    //setear frames a "60"
	    grafico->device->getTimer()->start();
	    for(u32 t=grafico->device->getTimer()->getTime();
            t+16>grafico->device->getTimer()->getTime();
            grafico->device->getTimer()->tick()
         );
        dibujarMenu();
        if(pa->input->receiver->IsKeyDown(irr::KEY_DOWN))
        {
            ((MenuContenedor*)elementos[4])->avanzar();
        }
        if(pa->input->receiver->IsKeyDown(irr::KEY_UP))
        {
            ((MenuContenedor*)elementos[4])->retroceder();
        }
        if(pa->input->receiver->IsKeyDown(irr::KEY_RIGHT))
        {
            if(((MenuContenedor*)elementos[4])->getSeleccionado()->getTipo()==5)
            {
                ((MenuLista*)((MenuContenedor*)elementos[4])->getSeleccionado())->actual++;
            }
            if(((MenuContenedor*)elementos[4])->getSeleccionado()->getTipo()==6)
            {
                ((MenuBarra*)((MenuContenedor*)elementos[4])->getSeleccionado())->actual++;
            }
        }
        if(pa->input->receiver->IsKeyDown(irr::KEY_LEFT))
        {
            if(((MenuContenedor*)elementos[4])->getSeleccionado()->getTipo()==5)
            {
                ((MenuLista*)((MenuContenedor*)elementos[4])->getSeleccionado())->actual--;
            }
            if(((MenuContenedor*)elementos[4])->getSeleccionado()->getTipo()==6)
            {
                ((MenuBarra*)((MenuContenedor*)elementos[4])->getSeleccionado())->actual--;
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
