#include "../include/Input.h"

Input::Input()
{
    tecla_arriba=true;
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

stringw Input::getInputKeyboard()
{
    stringw input="5";

    if(IsKeyDown(irr::KEY_KEY_S) && IsKeyDown(irr::KEY_KEY_A))
        input="1";
    else if(IsKeyDown(irr::KEY_KEY_S) && IsKeyDown(irr::KEY_KEY_D))
        input="3";
    else if(IsKeyDown(irr::KEY_KEY_W) && IsKeyDown(irr::KEY_KEY_A))
        input="7";
    else if(IsKeyDown(irr::KEY_KEY_W) && IsKeyDown(irr::KEY_KEY_D))
        input="9";
    else if(IsKeyDown(irr::KEY_KEY_S))
        input="2";
    else if(IsKeyDown(irr::KEY_KEY_A))
        input="4";
    else if(IsKeyDown(irr::KEY_KEY_D))
        input="6";
    else if(IsKeyDown(irr::KEY_KEY_W))
        input="8";
    if(tecla_arriba)
    {
        tecla_arriba=false;
        if(IsKeyDown(irr::KEY_KEY_U))
            input="a";
        else if(IsKeyDown(irr::KEY_KEY_I))
            input="b";
        else if(IsKeyDown(irr::KEY_KEY_O))
            input="c";
        else if(IsKeyDown(irr::KEY_KEY_J))
            input="d";
        else if(IsKeyDown(irr::KEY_KEY_K))
            input="e";
    }
    if(!IsKeyDown(irr::KEY_KEY_U) && !IsKeyDown(irr::KEY_KEY_I) && !IsKeyDown(irr::KEY_KEY_O) && !IsKeyDown(irr::KEY_KEY_J) && !IsKeyDown(irr::KEY_KEY_K) && !IsKeyDown(irr::KEY_KEY_L))
        tecla_arriba=true;

    return input;
}

stringw Input::getInputJoystick()
{
    stringw input="5";
    const SEvent::SJoystickEvent & joystickData = GetJoystickState();
    moveHorizontal =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
    moveVertical =(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;

    if(moveHorizontal<0 && moveVertical<0)
        input="1";
    else if(moveHorizontal>0 && moveVertical<0)
        input="3";
    else if(moveHorizontal<0 && moveVertical>0)
        input="7";
    else if(moveHorizontal>0 && moveVertical>0)
        input="9";
    else if(moveVertical<0)
        input="2";
    else if(moveHorizontal<0)
        input="4";
    else if(moveHorizontal>0)
        input="6";
    else if(moveVertical>0)
        input="8";
    if(tecla_arriba2)
    {
        tecla_arriba2=false;
        if(joystickData.IsButtonPressed(0))
            input="a";
        else if(joystickData.IsButtonPressed(1))
            input="b";
        else if(joystickData.IsButtonPressed(2))
            input="c";
        else if(joystickData.IsButtonPressed(3))
            input="d";
        else if(joystickData.IsButtonPressed(4))
            input="e";
    }
    if(!joystickData.IsButtonPressed(0) && !joystickData.IsButtonPressed(1) && !joystickData.IsButtonPressed(2) && !joystickData.IsButtonPressed(3) && !joystickData.IsButtonPressed(4) && !joystickData.IsButtonPressed(5))
        tecla_arriba2=true;
    return input;
}

bool Input::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool Input::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    //Joystick
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
    {
            JoystickState = event.JoystickEvent;
    }
    return false;
}

const SEvent::SJoystickEvent & Input::GetJoystickState(void) const
{
    return JoystickState;
}
