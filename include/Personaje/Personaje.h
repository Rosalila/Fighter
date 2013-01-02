#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Personaje/Movimiento.h"
#include "Personaje/InputMovimiento.h"
#include "Personaje/Proyectil.h"
#include "Sonido/Sonido.h"
#include "Personaje/Animacion.h"
#include "Personaje/Paleta.h"
#include "Input/Input.h"

class Personaje
{
    public:
    //Otras
    Personaje *personaje_contrario;
    Painter* painter;
    Input* input;
    Sonido* sonido;

    std::string char_name;
    char* char_name_ptr;
    int comparacion_hp;
    int comparacion_hp_contrario;
    int numero;
    int combo;
    int stage_piso;
    int px_colision,py_colision;
    int num_paleta;
    int proyectiles_activos;
    int px_inicial;
    int py_inicial;

    //efecto
    std::vector<Imagen>sombra;
    std::vector<int>sombra_x;
    std::vector<int>sombra_y;
    std::vector<bool>flip_sombra;
    Paleta paleta;

    //Otros std::vectores
    std::vector<Animacion>animaciones_back;
    std::vector<Animacion>animaciones_front;
    std::vector<Animacion>animaciones_actuales_back;
    std::vector<Animacion>animaciones_actuales_front;
    std::vector<InputMovimiento>inputs;
    std::vector<Movimiento*> movimientos_constantes_actuales;
    std::vector<Proyectil*> proyectiles_actuales;
    std::vector<Barra> barras;

    //vectores potenciales
    std::vector<SDL_Surface*>textures;

    //strings
    irr::core::map<std::string,std::string> strings;
    //imagenes
    irr::core::map<std::string,Imagen> imagenes;
    //ints
    irr::core::map<std::string,int> enteros;
    //hitboxes
    irr::core::map<std::string,vector<HitBox> > hitboxes;
    //movimientos
    irr::core::map<std::string,Movimiento*> movimientos;

    Personaje(Painter* painter,Sonido* sonido,int numero,int paleta);
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
    void dibujarImagenCameraAlign(Painter*painter,Imagen imagen,int posicion_x,int posicion_y);
    void dibujarImagen(Painter*painter,Imagen imagen,int posicion_x,int posicion_y);
    void dibujarAnimacionesBack();
    void dibujarAnimacionesFront();
    void dibujarHitBoxes(std::string variable,std::string path,bool izquierda,int x,int y);
    void dibujarBarras();
    void dibujarBarra(Barra barra);
    void dibujarBarraPequena(Barra barra,int cambio_x,int cambio_y);
    void dibujarProyectiles();
    //GETS shortcuts
    Movimiento* getMovimientoActual();
    Frame getFrameActual();
    //GETS variables
    int getEntero(std::string variable);
    Barra getBarra(std::string variable);
    std::vector<HitBox> getHitBoxes(std::string variable);
    Imagen getImagen(std::string variable);
    std::string getString(std::string variable);
    //SETS variables
    void setImagen(std::string variable,Imagen valor);
    void setEntero(std::string variable,int valor);
    void agregarBarra(Barra valor);
    void setHitBoxes(std::string variable,vector<HitBox> valor);
    void setString(std::string variable,std::string valor);
    //Agregares
    void agregarInput(vector<std::string> input,std::string movimiento);
    void agregarInput(std::string input,std::string movimiento);
    void agregarCondicion(std::string movimiento,int frame,vector<Condicion*> condicion);
    //void agregarCondicion(std::string movimiento,int frame,int posicion,Condicion condicion);
    void agregarMovimiento(std::string movimiento,int damage,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low);
    void agregarProyectil(Proyectil* proyectil);
    void agregarFrame(std::string movimiento, int duracion);
    void agregarModificador(std::string movimiento,int frame,std::string variable,Imagen modificador,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    void agregarModificador(std::string movimiento,int frame,std::string variable,Barra modificador,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string variable,vector <HitBox> modificador,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string modificador,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string tipo,std::string variable,std::string variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    //Logica
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(vector<HitBox> hb_azules,vector<HitBox> hb_rojas,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    void logicaBarras();
    void logicaProyectiles();
    void aplicarModificadores(vector<Modificador>,bool flip);
    void flipHitBoxes();
    std::string mapInputToMovimiento();
    bool cumpleCondiciones(std::string str_movimiento);
    bool cumpleCondiciones(vector<vector<Condicion*> >);
    bool cumpleCondicion(Condicion* condicion);
    bool inputEstaEnBuffer(vector<std::string> input,vector<std::string> buffer);
    void resetPersonaje();
    //Aplicar modificadores
    void aplicarModificador(ModificadorImagen* mi);
    void aplicarModificador(ModificadorEntero* me,bool flip);
    void aplicarModificador(ModificadorString* ms);
    void aplicarModificador(ModificadorHitboxes* mh);
    void aplicarModificador(ModificadorPorVariable* mv);
    void aplicarEfectosProyectiles();
};

#endif
