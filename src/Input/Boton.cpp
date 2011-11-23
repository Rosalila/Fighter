#include "Input/Boton.h"

Boton::Boton(Receiver* receiver,irr::EKEY_CODE teclado,stringw mapeo)
{
    this->teclado=teclado;
    this->mapeo=mapeo;
    usando_joystick=false;
    this->receiver=receiver;
}

Boton::Boton(Receiver* receiver,int joystick,int num_joystick,stringw mapeo)
{
    this->num_joystick=num_joystick;
    this->joystick=joystick;
    this->mapeo=mapeo;
    usando_joystick=true;
    this->receiver=receiver;
}

bool Boton::estaPresionado()
{
    if(usando_joystick)
    {
        if(receiver->IsJoyDown(joystick,num_joystick))
            return true;
    }else
    {
        if (receiver->IsKeyDown(teclado))
            return true;
    }
    return false;
}

stringw Boton::getMapeo()
{
    return mapeo;
}
