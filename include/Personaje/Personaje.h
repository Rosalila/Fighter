#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Personaje/Movimiento.h"
#include "Personaje/InputMovimiento.h"
#include "Personaje/Proyectil.h"
#include "Sonido/Sonido.h"
#include "Personaje/Animacion.h"
#include "Personaje/Paleta.h"

class Personaje
{
    public:
    //Otras
    Personaje *personaje_contrario;
    Grafico* grafico;
    Input* input;
    Sonido* sonido;

    stringw char_name;
    char* char_name_ptr;
    int comparacion_hp;
    int comparacion_hp_contrario;
    int numero;
    int combo;
    int stage_piso;
    int px_colision,py_colision;
    int num_paleta;
    int proyectiles_activos;

    //efecto
    vector<Imagen>sombra;
    vector<int>sombra_x;
    vector<int>sombra_y;
    vector<bool>flip_sombra;
    Paleta paleta;

    //Otros vectores
    vector<Animacion>animaciones_back;
    vector<Animacion>animaciones_front;
    vector<Animacion>animaciones_actuales_back;
    vector<Animacion>animaciones_actuales_front;
    vector<InputMovimiento>inputs;
    vector<Movimiento*> movimientos_constantes_actuales;
    vector<Proyectil*> proyectiles_actuales;
    vector<Barra> barras;

    //vectores potenciales
    vector<video::ITexture*>textures;

    //strings
    irr::core::map<stringw,stringw> strings;
    //imagenes
    irr::core::map<stringw,Imagen> imagenes;
    //ints
    irr::core::map<stringw,int> enteros;
    //hitboxes
    irr::core::map<stringw,vector<HitBox> > hitboxes;
    //movimientos
    irr::core::map<stringw,Movimiento*> movimientos;

    Personaje(Grafico* grafico,Sonido* sonido,int numero,int paleta);
    ~Personaje();
    //Cargares
    void cargarDesdeXML(int px,int py,Input* input,char* nombre);
    void cargarArchivo(char* archivo_xml);
    void cargarMain();
    void cargarVars();
    void cargarInputs();
    void cargarTriggers();
    void cargarSprites();
    void cargarHitboxes();
    void cargarSfx();
    void cargarAnimations();
    //Dibujares
    void dibujar();
    void dibujarImagenCameraAlign(Grafico*grafico,Imagen imagen,int posicion_x,int posicion_y);
    void dibujarImagen(Grafico*grafico,Imagen imagen,int posicion_x,int posicion_y);
    void dibujarAnimacionesBack();
    void dibujarAnimacionesFront();
    void dibujarHitBoxes(stringw variable,stringw path,bool izquierda,int x,int y);
    void dibujarBarras();
    void dibujarBarra(Barra barra);
    void dibujarBarraPequena(Barra barra,int cambio_x,int cambio_y);
    void dibujarProyectiles();
    //GETS shortcuts
    Movimiento* getMovimientoActual();
    Frame getFrameActual();
    //GETS variables
    int getEntero(stringw variable);
    Barra getBarra(stringw variable);
    vector<HitBox> getHitBoxes(stringw variable);
    Imagen getImagen(stringw variable);
    stringw getString(stringw variable);
    //SETS variables
    void setImagen(stringw variable,Imagen valor);
    void setEntero(stringw variable,int valor);
    void agregarBarra(Barra valor);
    void setHitBoxes(stringw variable,vector<HitBox> valor);
    void setString(stringw variable,stringw valor);
    //Agregares
    void agregarInput(vector<stringw> input,stringw movimiento);
    void agregarInput(stringw input,stringw movimiento);
    void agregarCondicion(stringw movimiento,int frame,vector<Condicion*> condicion);
    //void agregarCondicion(stringw movimiento,int frame,int posicion,Condicion condicion);
    void agregarMovimiento(stringw movimiento,int damage,bool multihit);
    void agregarProyectil(Proyectil* proyectil);
    void agregarFrame(stringw movimiento, int duracion);
    void agregarModificador(stringw movimiento,int frame,stringw variable,Imagen modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    void agregarModificador(stringw movimiento,int frame,stringw variable,Barra modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw variable,vector <HitBox> modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    //Logica
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(vector<HitBox> hb_azules,vector<HitBox> hb_rojas,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    void logicaBarras();
    void logicaProyectiles();
    void aplicarModificadores(vector<Modificador>,bool flip);
    void flipHitBoxes();
    stringw mapInputToMovimiento();
    bool cumpleCondiciones(stringw str_movimiento);
    bool cumpleCondiciones(vector<vector<Condicion*> >);
    bool cumpleCondicion(Condicion* condicion);
    bool inputEstaEnBuffer(vector<stringw> input,vector<stringw> buffer);
    //Aplicar modificadores
    void aplicarModificador(ModificadorImagen* mi);
    void aplicarModificador(ModificadorEntero* me,bool flip);
    void aplicarModificador(ModificadorString* ms);
    void aplicarModificador(ModificadorHitboxes* mh);
    void aplicarModificador(ModificadorPorVariable* mv);
    void aplicarEfectosProyectiles();
};

#endif
