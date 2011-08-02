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

class Input : public IEventReceiver
{
private:
    bool tecla_arriba;
    bool tecla_arriba2;
    irr::core::map<irr::EKEY_CODE,stringw> inputs;
    vector<irr::EKEY_CODE> teclas_cruz;
    vector<irr::EKEY_CODE> teclas_botones;
    SEvent::SJoystickEvent JoystickState;
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    virtual bool OnEvent(const SEvent& event);
    const SEvent::SJoystickEvent & GetJoystickState(void) const;
public:
    Input();
    core::stringw getInputKeyboard();
    string getInpurKeaboarCruz();
    string getInpurKeaboardBotones();
    core::stringw getInputJoystick();
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
    //stringw getInputString(const irr::EKEY_CODE* first, ...);
};

#endif // MYEVENTRECEIVER_H
