#include "Input/Receiver.h"

class Boton
{
private:
    irr::EKEY_CODE teclado;
    int joystick;
    stringw mapeo;
    bool usando_joystick;
    int num_joystick;
public:
    Boton(){}
    Boton(irr::EKEY_CODE teclado,stringw mapeo);
    Boton(int joystick,int num_joystick,stringw mapeo);
    bool estaPresionado(Receiver* receiver);
    stringw getMapeo();
};
