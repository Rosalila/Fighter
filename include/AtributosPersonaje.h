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
    int valor_maximo;
    int valor_actual;
    int modificador_periodico;
    int periodo;
    video::SColor color;
    core::rect<s32> posicion;
    irr::video::ITexture* imagenes[];

    Barra(int valor_maximo,int valor_actual,int modificador_periodico,int periodo,video::SColor color,core::rect<s32> posicion,irr::video::ITexture* imagenes[]);
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
    bool relativo;
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
    //entero
    stringw comparacion;
    int entero;
    //cadena
    stringw cadena;
    Condicion(int entero,stringw comparacion,stringw variable)
    {
        tipo=L"entero";
        this->comparacion=comparacion;
        this->entero=entero;
    }
    Condicion(stringw cadena,stringw variable)
    {
        tipo=L"cadena";
        this->cadena=cadena;
        this->variable=variable;
    }
};

class Frame
{
    public:
    vector <Modificador> modificadores;
    vector <Condicion> condiciones;
    int duracion;
    Frame(int duracion);
    //modificadores
    void agregarModificador(Imagen modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(int modificador,stringw variable,bool relativo,bool aplicar_a_contrario);
    void agregarModificador(Barra modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw modificador,stringw variable,bool aplicar_a_contrario);

    //condiciones
    void agregarCondicion(Condicion condicion)
    {
        condiciones.push_back(condicion);
    }
};

class Movimiento
{
    public:
    int frame_actual;
    vector <Frame> frames;
    Movimiento();
    Frame getFrameActual();
    void agregarFrame(int duracion);
    void agregarCondicion(Condicion condicion,int frame)
    {
        frames[frame].condiciones.push_back(condicion);
    }
};

class InputMovimiento
{
public:
    stringw input;
    stringw movimiento;
    InputMovimiento(stringw input,stringw movimiento)
    {
        this->input=input;
        this->movimiento=movimiento;
    }
};
