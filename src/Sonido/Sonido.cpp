#include "Sonido/Sonido.h"

Sonido::Sonido()
{
    engine=createIrrKlangDevice();
}
void Sonido::drop()
{
    engine->drop();
}
void Sonido::agregarSonido(stringw variable,const ik_c8* valor)
{
    if(sonidos.find(variable)==0)
        sonidos[variable]=new Reproduccion(engine->addSoundSourceFromFile(valor));
}
void Sonido::reproducirSonido(stringw variable)
{
    if(sonidos.find(variable)==0)
        return;
    Reproduccion* rep=sonidos[variable];
    rep->sonido=engine->play2D(rep->source,false,false,true,true);
}

void Sonido::pararSonido(stringw variable)
{
    if(sonidos.find(variable)==0)
        return;
    Reproduccion* rep=sonidos[variable];
    if(rep->sonido==NULL)
        return;
    rep->sonido->stop();
}

void Sonido::setVolumen(stringw variable,float volumen)
{
    if(sonidos.find(variable)==0)
        return;
    Reproduccion* rep=sonidos[variable];
    if(rep->sonido==NULL)
        return;
    rep->sonido->setVolume(volumen);
}
