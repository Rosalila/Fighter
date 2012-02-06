#include "Input/Receiver.h"

class Boton
{
private:


    bool usando_joystick;
    int num_joystick;
    Receiver* receiver;
public:
int joystick;
stringw mapeo;
irr::EKEY_CODE teclado;
    Boton(Receiver* receiver,irr::EKEY_CODE teclado,stringw mapeo);
    Boton(Receiver* receiver,int joystick,int num_joystick,stringw mapeo);
    bool estaPresionado();
    stringw getMapeo();
    stringw getInput();
    int getNumJoystick();
    bool usaJoystick();
    stringw keyToString();
};
