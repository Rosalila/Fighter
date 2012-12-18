#include "Sonido/Sonido.h"

Sonido::Sonido()
{
    cout<<"Initializing SLD sound engine."<<endl;cout.flush();
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        cout<<"Failed."<<endl;cout.flush();
        return;
    }
    cout<<"Success!"<<endl;cout.flush();
}

void Sonido::drop()
{
    //TODO for each chunk
    //Mix_FreeChunk( chunk );
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}
void Sonido::agregarSonido(stringw variable,std::string valor)
{
    if(sonidos.find(variable)==0)
        sonidos[variable]=Mix_LoadWAV(valor.c_str());
}
void Sonido::reproducirSonido(stringw variable,bool looped)
{
    if(sonidos.find(variable)==0)
        return;

    if(sonidos[variable]!=NULL)
    {
        if(looped)
            Mix_PlayChannel( -1, sonidos[variable], -1 );
        else
            Mix_PlayChannel( -1, sonidos[variable], 0 );
    }
}

void Sonido::playMusic(std::string path)
{
    stopMusic();
    cout<<"Playing music: "<<path<<endl;cout.flush();
    music = Mix_LoadMUS(path.c_str());
    Mix_PlayMusic(music,-1);
}

void Sonido::stopMusic()
{
    if(music!=NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music=NULL;
    }
}
