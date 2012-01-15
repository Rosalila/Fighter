#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdarg.h>
using namespace std;

#include <irrlicht/irrlicht.h>
#include "../include/TinyXml/tinyxml.h"

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
    SEvent::SJoystickEvent JoystickState0;
    SEvent::SJoystickEvent JoystickState1;
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    virtual bool OnEvent(const SEvent& event);
    const SEvent::SJoystickEvent & GetJoystickState(void) const;
    int joystick;
public:
    Receiver();
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
    bool IsJoyDown(int joyCode,int joystick);
};

#endif // MYEVENTRECEIVER_H>
