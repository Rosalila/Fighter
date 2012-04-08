#include "Input/Boton.h"
#include <IA/IA.h>

class Input
{
protected:
    vector<stringw> buffer_inputs;
    int jugador;

    Receiver* receiver;
public:
bool tecla_arriba;
IA *ia;
bool inteligencia_artificial;
vector<Boton> botones;
vector<Boton> cruz;
    Input(){}
    void cargarDesdeXML(int jugador,Receiver* receiver);
    void cargarIAXML(int jugador,char* archivo,char* archivo_default);
    TiXmlDocument* getXML(TiXmlDocument *doc);
    void actualizarBuffer();
    void actualizarBuffer(irr::core::map<stringw,stringw>*strings,
                          irr::core::map<stringw,stringw>*strings_contrario,
                          irr::core::map<stringw,int>*enteros,
                          irr::core::map<stringw,int>*enteros_contrario
                          );
    vector<stringw> getBufferInputs();
    void endEventProcess();
    void startEventProcess();
};
