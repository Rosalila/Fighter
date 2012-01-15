#include "Input/Boton.h"
#include <IA/IA.h>

class Input
{
protected:
    bool tecla_arriba;
    bool inteligencia_artificial;
    vector<Boton> cruz;
    vector<stringw> buffer_inputs;
    IA *ia;

    Receiver* receiver;
public:
vector<Boton> botones;
    Input(){}
    Input(vector<Boton> botones,Receiver* receiver,bool inteligencia_artificial);
    void cargarDesdeXML(int jugador,Receiver* receiver);
    void cargarIAXML(int jugador);
    void actualizarBuffer();
    vector<stringw> getBufferInputs();
};
