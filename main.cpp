#include "Rosalila/system.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

//SDL
#include "SDL2/SDL.h"
#include "Fighter.h"
#include "Rosalila/RosalilaUtility/RosalilaUtility.h"

#ifdef LINUX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef WINDOWS
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef OSX
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif

int main(int argc, char *argv[])
{
    //Clean the previous log
    clearLog();

    //OpenGL initialization
/* Died as glut did
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
*/

    //Input receiver initialization
    Receiver* receiver = new Receiver();

    //Graphics initialization
    RosalilaGraphics*painter = new RosalilaGraphics();
    painter->video(painter);

    //Sound initialization
    Sound*sonido = new Sound();

    //Menu initialization
    string menu_path=assets_directory+"menu/main_menu.svg";
    Menu* menu=new Menu(painter,receiver,sonido,menu_path.c_str());
    sonido->playMusic(menu->music_path);
    menu->loopMenu();

    return 0;
}
