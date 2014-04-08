#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Movimiento.h"
#include "InputMovimiento.h"
#include "Proyectil.h"
#include "RosalilaSound/RosalilaSound.h"
#include "Animacion.h"
#include "Paleta.h"
#include "RosalilaInputs/RosalilaInputs.h"
#include <map>

class Personaje
{
    public:
    //Otras
    Personaje *personaje_contrario;
    RosalilaGraphics* painter;
    RosalilaInputs* input;
    Sound* sonido;

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
    std::vector<Imagen*>sombra;
    std::vector<int>sombra_x;
    std::vector<int>sombra_y;
    std::vector<bool>flip_sombra;
    Paleta paleta;

    //Otros std::vectores
    std::vector<Animacion*>animaciones_back;
    std::vector<Animacion*>animaciones_front;
    std::vector<int>animaciones_actuales_back;
    std::vector<int>animaciones_actuales_front;
    std::vector<InputMovimiento*>inputs;
    std::vector<Movimiento*> movimientos_constantes_actuales;
    std::vector<Proyectil*> proyectiles_actuales;
    std::vector<Barra*> barras;

    //vectores potenciales
    std::vector<Image*>textures;

    //strings
    std::map<std::string,std::string> strings;
    //imagenes
    std::map<std::string,Imagen*> imagenes;
    //ints
    std::map<std::string,int> enteros;
    //hitboxes
    std::map<std::string,vector<HitBox*> > hitboxes;
    //movimientos
    std::map<std::string,Movimiento*> movimientos;

    Personaje(RosalilaGraphics* painter,Sound* sonido,int numero,int paleta);
    ~Personaje();
    //Cargares
    void loadFromXML(RosalilaInputs* input,char* nombre);
    void loadMain();
    void loadVars();
    void loadInputs();
    void loadTriggers();
    void loadSprites();
    void loadHitboxes();
    void loadSfx();
    void loadAnimations();
    void loadProjectiles();
    //Dibujares
    void dibujar();
    void dibujarImagenCameraAlign(RosalilaGraphics*painter,Imagen* imagen,int posicion_x,int posicion_y);
    void dibujarImagen(RosalilaGraphics*painter,Imagen* imagen,int posicion_x,int posicion_y);
    void dibujarAnimacionesBack();
    void dibujarAnimacionesFront();
    void dibujarHitBoxes(std::string variable,std::string path,bool izquierda,int x,int y);
    void dibujarBarras();
    void dibujarBarra(Barra* barra);
    void dibujarBarraPequena(Barra* barra,int cambio_x,int cambio_y);
    void dibujarProyectiles();
    //GETS shortcuts
    Movimiento* getMovimientoActual();
    Frame* getFrameActual();
    //GETS variables
    int getEntero(std::string variable);
    Barra* getBarra(std::string variable);
    std::vector<HitBox*> getHitBoxes(std::string variable);
    Imagen* getImagen(std::string variable);
    std::string getString(std::string variable);
    //SETS variables
    void setImagen(std::string variable,Imagen* valor);
    void setEntero(std::string variable,int valor);
    void agregarBarra(Barra* valor);
    void setHitBoxes(std::string variable,vector<HitBox*> valor);
    void setString(std::string variable,std::string valor);
    //Agregares
    void agregarRosalilaInputs(vector<std::string> input,std::string movimiento);
    void agregarRosalilaInputs(std::string input,std::string movimiento);
    void agregarCondicion(std::string movimiento,int frame,vector<Condicion*> condicion);
    //void agregarCondicion(std::string movimiento,int frame,int posicion,Condicion condicion);
    void agregarMovimiento(std::string movimiento,int damage,int chip_damage,bool multihit,bool unblockable_air,bool unblockable_high,bool unblockable_low,int velocity_x,int velocity_y,int acceleration_x,int acceleration_y,bool inherits_velocity,bool pushes,int separate_blue,int separate_red,int repeat_from,bool land_cancelable,bool crouched,bool is_status,int stop_time_at,int resume_time_at,string cancel_on_hit,bool is_attack,bool friction,int final_velocity_x,int final_velocity_y,int final_acceleration_x,int final_acceleration_y);
    void agregarProyectil(Proyectil* proyectil);
    void agregarFrame(std::string movimiento, int duracion);
    void agregarModificador(std::string movimiento,int frame,std::string variable,Imagen* modificador,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    void agregarModificador(std::string movimiento,int frame,std::string variable,Barra modificador,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string variable,vector <HitBox*> modificador,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string modificador,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,std::string tipo,std::string variable,std::string variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    //Logica
    bool getColisionHitBoxes(HitBox* hb_azul,HitBox* hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(vector<HitBox*> hb_azules,vector<HitBox*> hb_rojas,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    void logicaBarras();
    void logicaProyectiles();
    void aplicarModificadores(vector<Modificador*>,bool flip);
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
