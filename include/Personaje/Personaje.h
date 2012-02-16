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
    int numero;

    vector<InputMovimiento> inputs;
    vector<Movimiento*> movimientos_constantes_actuales;
    vector<Proyectil*> proyectiles_actuales;
    vector<Barra> barras;

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

    Personaje(Grafico* grafico,Sonido* sonido,int numero);
    void cargarDesdeXML(int px,int py,Input* input,char* archivo_xml);
    void cargarArchivo(char* archivo_xml);
    //DIBUJAR
    void dibujar();
    void dibujarHitBoxes(stringw variable,stringw path,bool izquierda,int x,int y);
    void dibujarBarras();
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
    void agregarMovimiento(stringw movimiento);
    void agregarProyectil(Proyectil* proyectil);
    void agregarFrame(stringw movimiento, int duracion);
    void agregarModificador(stringw movimiento,int frame,stringw variable,Imagen modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw variable,int modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    void agregarModificador(stringw movimiento,int frame,stringw variable,Barra modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw variable,vector <HitBox> modificador,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw tipo,stringw variable,stringw variable_modificador,bool relativo,bool aplicar_a_contrario,bool flipeable);
    //Aplicar modificadores
    void aplicarModificador(ModificadorImagen* mi);
    void aplicarModificador(ModificadorEntero* me,bool flip);
    void aplicarModificador(ModificadorString* ms);
    void aplicarModificador(ModificadorHitboxes* mh);
    void aplicarModificador(ModificadorPorVariable* mv);
    //Logica
    void logicaBarras();
    void logicaProyectiles();
    void aplicarModificadores(vector<Modificador>,bool flip);
    void flipHitBoxes();
    stringw mapInputToMovimiento();
    bool cumpleCondiciones(stringw str_movimiento);
    bool cumpleCondiciones(vector<vector<Condicion*> >);
    bool cumpleCondicion(Condicion* condicion);
    bool inputEstaEnBuffer(vector<stringw> input,vector<stringw> buffer);
};
