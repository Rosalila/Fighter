#include "../include/Input.h"

Input::Input()
{
    tecla_arriba=true;
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;

    teclas_cruz.push_back(irr::KEY_KEY_S);
    inputs[irr::KEY_KEY_S]="2";
    teclas_cruz.push_back(irr::KEY_KEY_A);
    inputs[irr::KEY_KEY_A]="4";
    teclas_cruz.push_back(irr::KEY_KEY_D);
    inputs[irr::KEY_KEY_D]="6";
    teclas_cruz.push_back(irr::KEY_KEY_W);
    inputs[irr::KEY_KEY_W]="8";

    teclas_botones.push_back(irr::KEY_KEY_U);
    inputs[irr::KEY_KEY_U]="a";
    teclas_botones.push_back(irr::KEY_KEY_I);
    inputs[irr::KEY_KEY_I]="b";
    teclas_botones.push_back(irr::KEY_KEY_J);
    inputs[irr::KEY_KEY_J]="c";
    teclas_botones.push_back(irr::KEY_KEY_K);
    inputs[irr::KEY_KEY_K]="d";
}

stringw Input::getInpurKeaboardCruz()
{
    stringw input="";
    for(int i=0;i<(int)teclas_cruz.size();i++)
        if(IsKeyDown(teclas_cruz[i]))
            input+=inputs[teclas_cruz[i]];
    return input;
}

string Input::getInpurKeaboardBotones()
{
    string input="";
    if(tecla_arriba)
    {
        tecla_arriba=false;
        for(int i=0;i<(int)teclas_botones.size();i++)
            if(IsKeyDown(teclas_botones[i]))
                input+=inputs[teclas_botones[i]];
    }
    bool flag=false;
    for(int i=0;i<(int)teclas_botones.size();i++)
        if(IsKeyDown(teclas_botones[i]))
            flag=true;
    if(flag)
        tecla_arriba=true;
    return input;
}

stringw Input::getInputKeyboard()
{
    stringw input=getInpurKeaboardCruz()+getInpurKeaboardBotones();
    if(input=="")
        return "5";
    return input;
}

stringw Input::getInputJoystick()
{
    f32 moveHorizontal;
    f32 moveVertical;
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
