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
    Grafico*grafico=new Grafico(receiver);
    Sonido*sonido = new Sonido();

    Menu* menu=new Menu(grafico,receiver,sonido,(char*)"menu/main_menu.xml");
    menu->loopMenu();
    //Fighter *fighter=new Fighter();
    //fighter->mainLoop();
    return 0;
}
