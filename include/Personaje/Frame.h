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
    vector <Modificador> modificadores;
    vector < vector<Condicion*> > condiciones;
    int duracion;
    Frame(int duracion);
    //modificadores
    void agregarModificador(Imagen modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(int modificador,stringw variable,bool relativo,bool aplicar_a_contrario,bool flipeable);
    void agregarModificador(Barra modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw tipo,stringw variable_modificador,stringw variable,bool relativo,bool aplicar_a_contrario,bool flipeable);

    //condiciones
    void agregarCondicion(vector<Condicion*> condicion);
    //void agregarCondicion(int posicion,Condicion condicion);
};

#endif
