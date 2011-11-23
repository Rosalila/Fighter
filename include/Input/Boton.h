#include "Input/Receiver.h"

class Boton
{
private:
    irr::EKEY_CODE teclado;
    int joystick;
    stringw mapeo;
    bool usando_joystick;
    int num_joystick;
    Receiver* receiver;
public:
    Boton(){}
    Boton(Receiver* receiver,irr::EKEY_CODE teclado,stringw mapeo);
    Boton(Receiver* receiver,int joystick,int num_joystick,stringw mapeo);
    bool estaPresionado();
    stringw getMapeo();
};
