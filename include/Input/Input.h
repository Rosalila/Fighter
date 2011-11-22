#include "Input/Boton.h"

class Input
{
protected:
    bool tecla_arriba;
    vector<Boton> cruz;
    vector<stringw> buffer_inputs;
    vector<Boton> botones;
    Receiver* receiver;
public:
    Input(){}
    Input(vector<Boton> botones,Receiver* receiver);
    void cargarDesdeXML(int jugador,Receiver* receiver);
    void actualizarBuffer();
    vector<stringw> getBufferInputs();
};

