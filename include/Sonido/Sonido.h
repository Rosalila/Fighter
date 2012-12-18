#ifndef SONIDO_H
#define SONIDO_H

#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;
#include <string>
#include <vector>

#include <iostream>
using namespace std;

//SDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

class Sonido
{
    irr::core::map<stringw,Mix_Chunk*> sonidos;
    Mix_Music *music = NULL;
public:
    Sonido();
    void drop();
    void agregarSonido(stringw variable,std::string valor);
    void reproducirSonido(stringw variable,bool looped);
    void playMusic(std::string variable);
    void stopMusic();
};

#endif
