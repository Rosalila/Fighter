#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdarg.h>
using namespace std;

#include <irrlicht/irrlicht.h>
#include "../include/TinyXml/tinyxml.h"
#include "SDL/SDL.h"

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
    //bool KeyIsDown[KEY_KEY_CODES_COUNT];
       enum keyStatesENUM {UP, DOWN, PRESSED, RELEASED};

       // Enumeration for Event Handling State.
       enum processStateENUM {STARTED, ENDED};

       // Keyboard key states.
       keyStatesENUM keyState[KEY_KEY_CODES_COUNT];
       processStateENUM processState; // STARTED = handling events, ENDED = not handling events


    virtual bool OnEvent(const SEvent& event);
    const SEvent::SJoystickEvent & GetJoystickState(void) const;
    int joystick;
public:
    Receiver();
    bool IsKeyDownn(int keycode);
    bool IsKeyPressed(int keycode);
    bool IsJoyDown(int joyCode,int joystick);
    void endEventProcess();
    void startEventProcess();
    //SDL
    bool KEYS[322];//key pressed
    Uint8 *keystates;//key down
    void updateInputs();
};

#endif // MYEVENTRECEIVER_H>
