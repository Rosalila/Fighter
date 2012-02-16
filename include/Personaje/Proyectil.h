#include "Grafico/Grafico.h"
#include "Personaje/Imagen.h"
#include "Personaje/Frame.h"

class Proyectil
{
public:
    //variables
    stringw nombre;
    stringw posicion_x;
    stringw posicion_y;
    stringw imagen;
    stringw hitboxes;
    stringw estado;
    stringw orientacion;

    //logica
    vector<Imagen>sprites;
    int frame_actual,tiempo_transcurrido;
    vector <Frame> frames;
    Frame getFrameActual();
    void agregarFrame(int duracion);
    void agregarCondicion(vector<Condicion*> condicion,int frame);

    int sprite_actual;
    Proyectil(stringw nombre,stringw posicion_x,stringw posicion_y,stringw imagen,stringw hitboxes,stringw estado,stringw orientacion,vector<Imagen>sprites);
    void avanzarFrame();
};
