#include "../include/AtributosPersonaje.h"
class Personaje
{
    public:
    //Otras
    Personaje *personaje_contrario;
    Grafico* grafico;
    Input* input;

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

    Personaje(Barra hp,int px,int py,int a,stringw orientacion,Grafico* grafico);
    Personaje();
    //DIBUJAR
    void dibujar();
    void dibujarHitBoxes(stringw variable,video::SColor color,bool izquierda);
    void dibujarBarra(stringw variable);
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
    void agregarCancel(stringw cancelador,stringw cancelado);
    void agregarMovimiento(stringw movimiento);
    void agregarFrame(stringw movimiento, int duracion);
    void agregarModificador(stringw movimiento,int frame,Imagen modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,int modificador,stringw variable,bool relativo,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,Barra modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario);
    void agregarModificador(stringw movimiento,int frame,stringw modificador,stringw variable,bool aplicar_a_contrario);
    //Aplicar modificadores
    void aplicarModificador(ModificadorImagen* mi);
    void aplicarModificador(ModificadorEntero* me);
    void aplicarModificador(ModificadorString* ms);
    void aplicarModificador(ModificadorHitboxes* mh);
    //Logica
    bool ejectuarCancel(stringw input);
    bool verificarFinDeMovimiento();
    bool aplicarModificadores();
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,Personaje* atacado);
};
