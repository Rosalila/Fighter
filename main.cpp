#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

//SDL
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include <string>

//#include "RosalilaInputs/RosalilaInputs.h"
#include "Fighter.h"
#include "Rosalila/RosalilaUtility/RosalilaUtility.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    clearLog();
    //Creadas abierto
    Receiver* receiver=new Receiver();
    RosalilaInputs*inputa=new RosalilaInputs();
    RosalilaInputs*inputb=new RosalilaInputs();

    inputa->loadFromXML(1,receiver);
    inputb->loadFromXML(2,receiver);

    RosalilaGraphics*painter=new RosalilaGraphics();
    painter->video(painter);

//painter->update.start();|
//painter->fps.start();


    Sound*sonido = new Sound();
    Menu* menu=new Menu(painter,receiver,sonido,(char*)"menu/main_menu.svg");
    sonido->playMusic(menu->music_path);

    menu->loopMenu();
    return 0;
}
