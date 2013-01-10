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

const int max_joystick_inputs=50;

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
    bool JOYKEYS_player1[max_joystick_inputs];//joykey pressed
    bool JOYKEYS_player2[max_joystick_inputs];//joykey pressed
    bool joy_up_pressed_player_1;
    bool joy_down_pressed_player_1;
    bool joy_left_pressed_player_1;
    bool joy_right_pressed_player_1;
    bool joy_up_pressed_player_2;
    bool joy_down_pressed_player_2;
    bool joy_left_pressed_player_2;
    bool joy_right_pressed_player_2;
    Uint8 *keystates;//key down
    void updateInputs();
};

#endif // MYEVENTRECEIVER_H>
