#include "../include/AtributosPersonaje.h"

class Personaje
{
    public:
    //paja
    Personaje *personaje_contrario;
    Grafico* grafico;
    char* nombre;
    //logica
    char orientacion;
    std::string movimiento_actual;
    int tiempo_transcurrido;
    std::string estado_posicion;
    //bool saltando,saltando_adelante,saltando_atras;
    int frame_actual_saltando;
    //imagenes
    irr::core::map<std::string,video::ITexture*> imagenes;
    //ints
    irr::core::map<std::string,int> enteros;
    //barra
    irr::core::map<std::string,Barra> barras;
    //hitboxes
    irr::core::map<std::string,vector<HitBox> > hitboxes;
    //movimientos
    irr::core::map<std::string,Movimiento*> movimientos;

    Personaje(Barra hp,int px,int py,int a,char orientacion,Grafico* grafico);
    Personaje();
    //DIBUJAR
    void dibujar();
    void dibujarHitBoxes(std::string variable,video::SColor color);
    void dibujarBarra(std::string variable);
    //GETS shortcuts
    Movimiento* getMovimientoActual();
    Frame getFrameActual();
    //GETS variables
    int getEntero(std::string variable);
    Barra getBarra(std::string variable);
    vector<HitBox> getHitBoxes(std::string variable);
    video::ITexture* getImagen(std::string variable);
    //SETS variables
    void setImagen(std::string variable,video::ITexture* valor);
    void setEntero(std::string variable,int valor);
    void setBarra(std::string variable,Barra valor);
    void setHitBoxes(std::string variable,vector<HitBox> valor);
    //Agregares
    void agregarCancel(std::string cancelador,std::string cancelado);
    void agregarMovimiento(std::string movimiento);
    void agregarFrame(std::string movimiento, int duracion);
    void agregarModificador(std::string movimiento,int frame,video::ITexture* modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,int modificador,Personaje* personaje,std::string variable,bool relativo,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,Barra modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    void agregarModificador(std::string movimiento,int frame,vector <HitBox> modificador,Personaje* personaje,std::string variable,bool aplicar_a_contrario);
    //Logica
    bool ejectuarCancel(std::string input);
    bool verificarFinDeMovimiento();
    bool aplicarModificadores();
    bool getColisionHitBoxes(HitBox hb_azul,HitBox hb_roja,int atacado_x,int atacado_y,int atacante_x,int atacante_y);
    bool getColisionHitBoxes(Personaje *atacante,Personaje* atacado);
};
