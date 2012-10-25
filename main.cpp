#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

//#include "Input/Input.h"
#include "include/Fighter.h"

#include <iostream>
using namespace std;

int main()
{
    //Creadas abierto
    Receiver* receiver=new Receiver();
    Input*inputa=new Input();
    Input*inputb=new Input();
    inputa->cargarDesdeXML(1,receiver);
    inputb->cargarDesdeXML(2,receiver);
    Painter*painter=new Painter(receiver);
    Sonido*sonido = new Sonido();

    Menu* menu=new Menu(painter,receiver,sonido,(char*)"menu/main_menu.xml");
    sonido->reproducirSonido(stringw("Menu.music"),true);
    menu->loopMenu();
    //Fighter *fighter=new Fighter();
    //fighter->mainLoop();
    return 0;
}
