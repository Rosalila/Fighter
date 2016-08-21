#ifndef MODIFICADOR_H
#define MODIFICADOR_H

#include <vector>
#include "../Rosalila/RosalilaUtility/Hitbox.h"
#include "Imagen.h"
#include "Barra.h"
#include "../Rosalila/RosalilaGraphics/RosalilaGraphics.h"

class Modificador
{
    public:
    //info
    bool aplicar_a_contrario;
    std::string tipo;
    std::string variable;
    Imagen* modificador_imagen;

    bool relativo;//solo para ints
    std::string tipo_variable;//solo para por variables

    Barra modificador_barra;
    std::vector <Hitbox*> modificador_hitbox;
    std::string modificador_string;
    int modificador_entero;
    bool flipeable;
    ~Modificador()
    {
//        delete modificador_imagen;
//        for(;!modificadores.empty();)
//        {
//            Modificador*modificador=modificadores.back();
//            modificadores.pop_back();
//            delete modificador;
//        }
    }
};

#endif
