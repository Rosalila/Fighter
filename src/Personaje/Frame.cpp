#include "Personaje/Frame.h"

Frame::Frame(int duracion)
{
    this->modificadores=vector<Modificador>();
    this->duracion=duracion;
}
void Frame::agregarModificador(Imagen modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorImagen(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(int modificador,stringw variable,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    modificadores.push_back(ModificadorEntero(variable,modificador,relativo,aplicar_a_contrario,flipeable));
}
void Frame::agregarModificador(Barra modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorBarra(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(vector <HitBox> modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorHitboxes(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(stringw modificador,stringw variable,bool aplicar_a_contrario)
{
    modificadores.push_back(ModificadorString(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(stringw tipo,stringw variable_modificador,stringw variable,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    modificadores.push_back(ModificadorPorVariable(tipo,variable,variable_modificador,relativo,aplicar_a_contrario,flipeable));
}
void Frame::agregarCondicion(vector<Condicion*> condicion)
{
    condiciones.push_back(condicion);
}
