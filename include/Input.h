#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

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
    f32 moveHorizontal;
    f32 moveVertical;
    SEvent::SJoystickEvent JoystickState;
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    virtual bool OnEvent(const SEvent& event);
    const SEvent::SJoystickEvent & GetJoystickState(void) const;
public:
    Input();
    core::stringw getInputKeyboard();
    core::stringw getInputJoystick();
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
};

#endif // MYEVENTRECEIVER_H
