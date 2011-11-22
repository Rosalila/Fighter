#include "Grafico/Grafico.h"
#include "Personaje/Frame.h"

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
