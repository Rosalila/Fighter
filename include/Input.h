#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <vector>
#include <stdarg.h>
using namespace std;

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Receiver : public IEventReceiver
{
private:
    f32 moveHorizontal;
    f32 moveVertical;
    SEvent::SJoystickEvent JoystickState;
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    virtual bool OnEvent(const SEvent& event);
    const SEvent::SJoystickEvent & GetJoystickState(void) const;

public:
    Receiver();
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
    bool IsJoyDown(int joyCode);
};

class Boton
{
private:
    irr::EKEY_CODE teclado;
    int joystick;
    stringw mapeo;
    bool usando_joystick;
public:
    Boton(irr::EKEY_CODE teclado,stringw mapeo)
    {
        this->teclado=teclado;
        this->mapeo=mapeo;
        usando_joystick=false;
    }
    Boton(int joystick,stringw mapeo)
    {
        this->joystick=joystick;
        this->mapeo=mapeo;
        usando_joystick=true;
    }

    bool estaPresionado(Receiver* receiver)
    {
        if(usando_joystick)
        {
            if(receiver->IsJoyDown(joystick))
                return true;
        }else
        {
            if (receiver->IsKeyDown(teclado))
                return true;
        }
        return false;
    }

    stringw getMapeo()
    {
        return mapeo;
    }
};

class Input
{
private:
    Receiver* receiver;
    bool tecla_arriba;
    vector<Boton> botones;
    vector<stringw> buffer_inputs;
public:
    Input(vector<Boton> botones,Receiver* receiver);
    stringw getInput();
    vector<stringw> getBufferInputs();
};

#endif // MYEVENTRECEIVER_H
