#include "Personaje/Movimiento.h"

Movimiento::Movimiento(stringw nombre)
{
    frame_actual=0;
    tiempo_transcurrido=0;
    this->nombre=nombre;
}
Frame Movimiento::getFrameActual()
{
    return frames[frame_actual];
}
void Movimiento::agregarFrame(int duracion)
{
    frames.push_back(Frame(duracion));
}

void Movimiento::agregarCondicion(vector<Condicion*> condicion,int frame)
{
    frames[frame].condiciones.push_back(condicion);
}

//void Movimiento::agregarCondicion(int posicion,Condicion condicion,int frame)
//{
//    frames[frame].condiciones[posicion].push_back(condicion);
//}
