#include "../include/Input.h"

Input::Input(vector<Boton> botones,Receiver* receiver)
{
    this->receiver=receiver;
    tecla_arriba=true;

    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
    this->botones=botones;
}

stringw Input::getInput()
{
    stringw resultado="";
    if(tecla_arriba)
    {
        tecla_arriba=false;
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].estaPresionado(receiver))
                resultado+=botones[i].getMapeo();
    }
    bool flag=false;
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].estaPresionado(receiver))
            flag=true;
    if(flag)
        tecla_arriba=true;
    if(resultado=="")
        resultado="5";
    buffer_inputs.insert(buffer_inputs.begin(),resultado);
    buffer_inputs.pop_back();
    return resultado;
}

vector<stringw> Input::getBufferInputs()
{
    return buffer_inputs;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

Receiver::Receiver()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool Receiver::OnEvent(const SEvent& event)
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

const SEvent::SJoystickEvent & Receiver::GetJoystickState(void) const
{
    return JoystickState;
}

bool Receiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool Receiver::IsJoyDown(int joyCode)
{
    const SEvent::SJoystickEvent & joystickData = GetJoystickState();
    moveHorizontal=(f32)JoystickState.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
    moveVertical=(f32)JoystickState.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
    if(moveVertical<0 && joyCode==-2)
        return true;
    if(moveHorizontal<0 && joyCode==-4)
        return true;
    if(moveHorizontal>0 && joyCode==-6)
        return true;
    if(moveVertical>0 && joyCode==-8)
        return true;
    if(joystickData.IsButtonPressed(joyCode))
        return true;
    return false;
}
