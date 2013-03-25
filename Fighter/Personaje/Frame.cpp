#include "Personaje/Frame.h"

Frame::Frame(int duracion)
{
    this->modificadores=std::vector<Modificador*>();
    this->duracion=duracion;
}

Frame::~Frame()
{
    for(;!modificadores.empty();)
    {
        Modificador*modificador=modificadores.back();
        modificadores.pop_back();
        delete modificador;
    }

    for(;!condiciones.empty();)
    {
        std::vector<Condicion*>cond=condiciones.back();
        condiciones.pop_back();
        for(;!cond.empty();)
        {
            Condicion*condicion=cond.back();
            cond.pop_back();
            delete condicion;
        }
    }
}

void Frame::agregarModificador(Imagen* modificador,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(new ModificadorImagen(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(int modificador,std::string variable,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    modificadores.push_back(new ModificadorEntero(variable,modificador,relativo,aplicar_a_contrario,flipeable));
}
void Frame::agregarModificador(Barra modificador,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(new ModificadorBarra(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(std::vector <HitBox*> modificador,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(new ModificadorHitboxes(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(std::string modificador,std::string variable,bool aplicar_a_contrario)
{
    modificadores.push_back(new ModificadorString(variable,modificador,aplicar_a_contrario));
}
void Frame::agregarModificador(std::string tipo,std::string variable_modificador,std::string variable,bool relativo,bool aplicar_a_contrario,bool flipeable)
{
    modificadores.push_back(new ModificadorPorVariable(tipo,variable,variable_modificador,relativo,aplicar_a_contrario,flipeable));
}
void Frame::agregarCondicion(std::vector<Condicion*> condicion)
{
    condiciones.push_back(condicion);
}
