#ifndef FRAME_H
#define FRAME_H

#include "Personaje/Modificador.h"
#include "Personaje/ModificadorBarra.h"
#include "Personaje/ModificadorEntero.h"
#include "Personaje/ModificadorHitboxes.h"
#include "Personaje/ModificadorImagen.h"
#include "Personaje/ModificadorPorVariable.h"
#include "Personaje/ModificadorString.h"
#include "Personaje/Condicion.h"

class Frame
{
    public:
    std::vector <Modificador*> modificadores;
    std::vector < std::vector<Condicion*> > condiciones;
    int duracion;
    Frame(int duracion);
    ~Frame();
    //modificadores
    void agregarModificador(Imagen* modificador,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(int modificador,std::string variable,bool relativo,bool aplicar_a_contrario,bool flipeable);
    void agregarModificador(Barra modificador,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::vector <HitBox*> modificador,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::string modificador,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::string tipo,std::string variable_modificador,std::string variable,bool relativo,bool aplicar_a_contrario,bool flipeable);

    //condiciones
    void agregarCondicion(std::vector<Condicion*> condicion);
    //void agregarCondicion(int posicion,Condicion condicion);
};

#endif
