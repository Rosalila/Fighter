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
    int jugador;

    Receiver* receiver;
public:
vector<Boton> botones;
    Input(){}
    void cargarDesdeXML(int jugador,Receiver* receiver);
    void cargarIAXML(int jugador);
    TiXmlDocument* getXML(TiXmlDocument *doc);
    void actualizarBuffer();
    vector<stringw> getBufferInputs();
};
