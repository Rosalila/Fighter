#include <vector>
#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include "../include/Grafico.h"
#include "../include/Sonido.h"

class Personaje;

class Barra
{
public:
    stringw valor_maximo;
    stringw valor_actual;
    stringw modificador_periodico;
    stringw periodo;
    video::SColor color;
    core::rect<s32> posicion;
    irr::video::ITexture* imagenes[];

    Barra(stringw valor_maximo,stringw valor_actual,stringw modificador_periodico,stringw periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagenes[]);
    Barra();
};

class HitBox
{
public:
    int p1x,p1y,p2x,p2y;

    HitBox (int p1x,int p1y,int p2x,int p2y);
};

class Imagen
{
public:
    int dimension_x,dimension_y,alineacion_x,alineacion_y,escala;
    video::ITexture* imagen;

    Imagen(video::ITexture* imagen,float escala,int alineacion_x,int alineacion_y);
    Imagen(video::ITexture* imagen,int alineacion_x,int alineacion_y);
    Imagen();
};

class Modificador
{
    public:
    //info
    bool aplicar_a_contrario;
    stringw tipo;
    stringw variable;
    Imagen modificador_imagen;

    bool relativo;//solo para ints

    Barra modificador_barra;
    vector <HitBox> modificador_hitbox;
    stringw modificador_string;
    int modificador_entero;
};

class ModificadorImagen : public Modificador
{
    public:
    ModificadorImagen(Imagen modificador,stringw variable,bool aplicar_a_contrario);
};

class ModificadorEntero : public Modificador
{
    public:
    ModificadorEntero(int modificador,stringw variable,bool relativo,bool aplicar_a_contrario);
};

class ModificadorBarra : public Modificador
{
    public:
    ModificadorBarra(Barra modificador,stringw variable,bool aplicar_a_contrario);
};

class ModificadorHitboxes : public Modificador
{
    public:
    ModificadorHitboxes(vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario);
};

class ModificadorString : public Modificador
{
    public:
    ModificadorString(stringw modificador,stringw variable,bool aplicar_a_contrario);
};

class Condicion
{
public:
    stringw tipo;
    stringw variable;
    bool personaje_contrario;
    //entero
    stringw comparacion;
    int entero;
    //cadena
    stringw cadena;
    Condicion(stringw variable,stringw comparacion,int entero,bool personaje_contrario)
    {
        tipo=L"entero";
        this->variable=variable;
        this->comparacion=comparacion;
        this->entero=entero;
        this->personaje_contrario=personaje_contrario;
    }
    Condicion(stringw variable,stringw comparacion,stringw cadena,bool personaje_contrario)
    {
        tipo=L"cadena";
        this->variable=variable;
        this->comparacion=comparacion;
        this->cadena=cadena;
        this->personaje_contrario=personaje_contrario;
    }
    bool comparar(int c)
    {
        if(comparacion=="=")
            return c==entero;
        if(comparacion=="!=")
            return c!=entero;
        if(comparacion=="<")
            return c<entero;
        if(comparacion==">")
            return c>entero;
        if(comparacion=="<=")
            return c<=entero;
        if(comparacion==">=")
            return c>=entero;
        return false;
    }
    bool comparar(stringw s)
    {
        if(comparacion=="=")
            return s==cadena;
        if(comparacion=="!=")
            return s!=cadena;
        return false;
    }
};

class Frame
{
    public:
    vector <Modificador> modificadores;
    vector < vector<Condicion> > condiciones;
    int duracion;
    Frame(int duracion);
    //modificadores
    void agregarModificador(Imagen modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(int modificador,stringw variable,bool relativo,bool aplicar_a_contrario);
    void agregarModificador(Barra modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw modificador,stringw variable,bool aplicar_a_contrario);

    //condiciones
    void agregarCondicion(vector<Condicion> condicion)
    {
        condiciones.push_back(condicion);
    }
    void agregarCondicion(int posicion,Condicion condicion)
    {
        condiciones[posicion].push_back(condicion);
    }
};

class Movimiento
{
    public:
    stringw nombre;
    int frame_actual,tiempo_transcurrido;
    vector <Frame> frames;
    Movimiento(stringw nombre);
    Frame getFrameActual();
    void agregarFrame(int duracion);
    void agregarCondicion(vector<Condicion> condicion,int frame)
    {
        frames[frame].condiciones.push_back(condicion);
    }
    void agregarCondicion(int posicion,Condicion condicion,int frame)
    {
        frames[frame].condiciones[posicion].push_back(condicion);
    }
};

class InputMovimiento
{
public:
    vector<stringw> input;
    stringw movimiento;
    InputMovimiento(vector<stringw> input,stringw movimiento)
    {
        this->input=input;
        this->movimiento=movimiento;
    }
};
