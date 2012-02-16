#ifndef MODIFICADOR_H
#define MODIFICADOR_H

#include "Personaje/HitBox.h"
#include "Personaje/Imagen.h"
#include "Personaje/Barra.h"
#include "Grafico/Grafico.h"

class Modificador
{
    public:
    //info
    bool aplicar_a_contrario;
    stringw tipo;
    stringw variable;
    Imagen modificador_imagen;

    bool relativo;//solo para ints
    stringw tipo_variable;//solo para por variables

    Barra modificador_barra;
    vector <HitBox> modificador_hitbox;
    stringw modificador_string;
    int modificador_entero;
    bool flipeable;
};

#endif
