#include "Personaje/Movimiento.h"
#include "Personaje/InputMovimiento.h"
#include "Personaje/Proyectil.h"
#include "Sonido/Sonido.h"

class Personaje
{
    public:
    //Otras
    Personaje *personaje_contrario;
    Grafico* grafico;
    Input* input;
    Sonido* sonido;
    int comparacion_hp;
    int comparacion_hp_contrario;

    vector<InputMovimiento> inputs;
    vector<Movimiento*> movimientos_constantes_actuales;
    vector<Proyectil*> proyectiles_actuales;

    //strings
    irr::core::map<stringw,stringw> strings;
    //imagenes
    irr::core::map<stringw,Imagen> imagenes;
    //ints
    irr::core::map<stringw,int> enteros;
    //barra
    irr::core::map<stringw,Barra> barras;
    //hitboxes
    irr::core::map<stringw,vector<HitBox> > hitboxes;
    //movimientos
    irr::core::map<stringw,Movimiento*> movimientos;

    Personaje(Grafico* grafico,Sonido* sonido);
    void cargarDesdeXML(int px,int py,Input* input,char* archivo_xml);
    void cargarArchivo(char* archivo_xml);
    //DIBUJAR
    void dibujar();
    void dibujarHitBoxes(stringw variable,stringw path,bool izquierda,int x,int y);
    void dibujarBarra(stringw variable,int alineacion_x,int alineacion_y);
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
    void setBarra(stringw variable,Barra valor);
    void setHitBoxes(stringw variable,vector<HitBox> valor);
    void setString(stringw variable,stringw valor);
    //Agregares
    void agregarInput(vector<stringw> input,stringw movimiento);
    void agregarInput(stringw input,stringw movimiento);
    void agregarCondicion(stringw movimiento,int frame,vector<Condicion*> condicion);
    //void agregarCondicion(stringw movimiento,int frame,int posicion,Condicion condicion);
    void agregarMovimiento(stringw movimiento);
    void agregarProyectil(stringw nombre,stringw posicion_x,stringw posicion_y,stringw imagen,stringw hitboxes,stringw estado,stringw orientacion);
    void agregarFrame(stringw movimiento, int duracion);
    void agregarModificador(stringw movimiento,int frame,stringw variable,Imagen modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw variable,int modificador,bool relativo,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw variable,Barra modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw variable,vector <HitBox> modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario);
    //Aplicar modificadores
    void aplicarModificador(ModificadorImagen* mi);
    void aplicarModificador(ModificadorEntero* me);
    void aplicarModificador(ModificadorString* ms);
    void aplicarModificador(ModificadorHitboxes* mh);
    void aplicarModificador(ModificadorPorVariable* mv);
    //Logica
    void aplicarModificadores(vector<Modificador>);
    void flipHitBoxes();
    stringw mapInputToMovimiento();
    bool cumpleCondiciones(stringw str_movimiento);
    bool cumpleCondicion(Condicion* condicion);
    bool inputEstaEnBuffer(vector<stringw> input,vector<stringw> buffer);
};
