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
    SEvent::SJoystickEvent JoystickState;
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    virtual bool OnEvent(const SEvent& event);
public:
    Receiver();
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
    const SEvent::SJoystickEvent & GetJoystickState(void) const;
    //stringw getInputString(const irr::EKEY_CODE* first, ...);
};

class Input
{
private:

private:
    Receiver* receiver;
    bool usando_joystick;
    //Teclado
    bool tecla_arriba;
    irr::core::map<irr::EKEY_CODE,stringw> inputs;
    vector<irr::EKEY_CODE> teclas_cruz;
    vector<irr::EKEY_CODE> teclas_botones;
    core::stringw getInputKeyboard();
    stringw getInputKeyboardCruz();
    stringw getInputKeyboardBotones();

    //Joystick
    bool tecla_arriba2;
    irr::core::map<int,stringw> inputs_joystick;
    vector<int> joystick_botones;
    core::stringw getInputJoystick();
    stringw getInputJoystickCruz();
    stringw getInputJoystickBotones();

    //Pila
    vector<stringw> buffer_inputs;
public:
    stringw getInput();
    stringw getInputCruz();
    stringw getInputBotones();
    vector<stringw> getBufferInputs();
    Input(int i,Receiver* receiver);
    Input(stringw str,Receiver* receiver);
    Input();
};

#endif // MYEVENTRECEIVER_H
