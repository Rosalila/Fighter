#include "Input/Boton.h"
#include <IA/IA.h>

class Input
{
protected:
    bool tecla_arriba;
    vector<Boton> cruz;
    vector<stringw> buffer_inputs;
    int jugador;

    Receiver* receiver;
public:
IA *ia;
bool inteligencia_artificial;
vector<Boton> botones;
    Input(){}
    void cargarDesdeXML(int jugador,Receiver* receiver);
    void cargarIAXML(int jugador);
    TiXmlDocument* getXML(TiXmlDocument *doc);
    void actualizarBuffer(irr::core::map<stringw,stringw>*strings,irr::core::map<stringw,stringw>*strings_contrario);
    vector<stringw> getBufferInputs();
};
